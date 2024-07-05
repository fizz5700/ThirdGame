

#include "Enemy.h"
#include "AIController.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimMontage.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "../HUD/HealthBarComponent.h"
#include "../Components/AttributeComponent.h"
#include "../HUD/HealthBarComponent.h"
AEnemy::AEnemy()
{
	
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility,ECollisionResponse::ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	
	Attributes = CreateAbstractDefaultSubobject<UAttributeComponent>(TEXT("Attributes"));
	HealthBarWidget= CreateAbstractDefaultSubobject<UHealthBarComponent>(TEXT("HealthBar"));
	HealthBarWidget->SetupAttachment(GetRootComponent());

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
	PawnSensing->SightRadius = 4000.f;
	PawnSensing->SetPeripheralVisionAngle(45.f);

}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	EnemyController = Cast<AAIController>(GetController());

	if (HealthBarWidget) {
		HealthBarWidget->SetVisibility(false);
	}
	MoveToTarget(PatrolTarget);
	
	if (PawnSensing) {
		PawnSensing->OnSeePawn.AddDynamic(this,&AEnemy::PawnSeen);
	}
}

bool AEnemy::InTarGetRange(AActor* Target, double Radius)
{
	if (Target==nullptr) return false;
	const double DistanceToTarget = (Target->GetActorLocation() - GetActorLocation()).Size();
	return DistanceToTarget<=Radius;
}



void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (EnemyState > EEnemyState::EES_Patrolling) {
		CheckCombatTarget();
	}
	else {
		CheckPartroTarget();
	}
	
	
}

void AEnemy::CheckPartroTarget()
{
	if (InTarGetRange(PatrolTarget, PatrolRadius)) {
		PatrolTarget = choosePatrolTarget();
		if (PatrolTarget) {
			GetWorldTimerManager().SetTimer(PatroTimer, this, &AEnemy::PatroTimerFinished, FMath::RandRange(5.f, 10.f));
		}
	}
}

void AEnemy::CheckCombatTarget()
{
	if (!InTarGetRange(CombatTarget, CombarRadius)) {
		CombatTarget = nullptr;
		if (HealthBarWidget) {
			HealthBarWidget->SetVisibility(false);
		}
		EnemyState = EEnemyState::EES_Patrolling;
		GetCharacterMovement()->MaxWalkSpeed = 125.f;
		MoveToTarget(PatrolTarget);
	}
	else if (!InTarGetRange(CombatTarget, AttackRadius)&& EnemyState != EEnemyState::EES_Chasing) {
		EnemyState = EEnemyState::EES_Chasing;
		GetCharacterMovement()->MaxWalkSpeed = 300.f;
		MoveToTarget(CombatTarget);
	}
	else if (InTarGetRange(CombatTarget, AttackRadius) && EnemyState != EEnemyState::EES_Attacking) {
		EnemyState = EEnemyState::EES_Attacking;
	}
}

void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::GetHit_Implementation(const FVector& ImpactPoint)
{
	//if (GetWorld()) DrawDebugSphere(GetWorld(), ImpactPoint, 8.f, 12, FColor::Red, false,5.f);
	if (HealthBarWidget) {
		HealthBarWidget->SetVisibility(true);
	}
	if (Attributes&& Attributes->IsAlive()) {
		DirectionalHitReact(ImpactPoint);
	}
	else
	{
		Die();
	}
	if (HitSound) {
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, ImpactPoint);
	}

	if (HitParticles&& GetWorld()) {
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticles, ImpactPoint);
	}

}
AActor* AEnemy::choosePatrolTarget()
{
	TArray<AActor*> ValidTargets;
	for (AActor* Target : PatrolTargets) {
		if (Target != PatrolTarget) {
			ValidTargets.AddUnique(Target);
		}
	}
	const int32 NumPatrolTargets = ValidTargets.Num();
	if (NumPatrolTargets > 0) {

		const int32 TargetSelection = FMath::RandRange(0, NumPatrolTargets - 1);
		return ValidTargets[TargetSelection];
	}

	return nullptr;
}
void AEnemy::PawnSeen(APawn* SeenPawn)
{
	if (EnemyState == EEnemyState::EES_Chasing) return;
	if (SeenPawn->ActorHasTag(FName("SlashCharacter"))) {
		GetWorldTimerManager().ClearTimer(PatroTimer);
		GetCharacterMovement()->MaxWalkSpeed=300.F;
		CombatTarget = SeenPawn;
		if (EnemyState != EEnemyState::EES_Attacking) {
			EnemyState = EEnemyState::EES_Chasing;
			MoveToTarget(CombatTarget);
		}
	}
	
}
void AEnemy::MoveToTarget(AActor* Target)
{
	if (EnemyController == nullptr || Target == nullptr) return;
	FAIMoveRequest MoveRequest;
	MoveRequest.SetGoalActor(Target);
	MoveRequest.SetAcceptanceRadius(AcceptanceRadius);
	EnemyController->MoveTo(MoveRequest);
}

void AEnemy::Die()
{
	if (HealthBarWidget) {
		HealthBarWidget->SetVisibility(false);
	}
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && DeathMontage) {
		AnimInstance->Montage_Play(DeathMontage);
		const int32 Selection = FMath::RandRange(0, 5);
		FName SectionName = FName();
		switch (Selection) {
		case 0:
			SectionName = FName("Death1");
			DeathPose = EDeathPose::EDP_Death1;
			break;
		case 1:
			SectionName = FName("Death2");
			DeathPose = EDeathPose::EDP_Death2;
			break;
		case 2:
			SectionName = FName("Death3");
			DeathPose = EDeathPose::EDP_Death3;
			break;
		case 3:
			SectionName = FName("Death4");
			DeathPose = EDeathPose::EDP_Death4;
			break;
		case 4:
			SectionName = FName("Death5");
			DeathPose = EDeathPose::EDP_Death5;
			break;
		case 5:
			SectionName = FName("Death6");
			DeathPose = EDeathPose::EDP_Death6;
			break;
		default:
			break;
		}
		AnimInstance->Montage_JumpToSection(SectionName, DeathMontage);
	}

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SetLifeSpan(3.F);

}

void AEnemy::DirectionalHitReact(const FVector& ImpactPoint)
{
	const FVector Front = GetActorForwardVector();
	const FVector ImpactLowered(ImpactPoint.X, ImpactPoint.Y, GetActorLocation().Z);
	const FVector HitFVector = (ImpactPoint - GetActorLocation()).GetSafeNormal();

	const double CosTeata = FVector::DotProduct(Front, HitFVector);
	double Theta = FMath::Acos(CosTeata);
	Theta = FMath::RadiansToDegrees(Theta);

	const FVector CrossProduct = FVector::CrossProduct(Front, HitFVector);
	if (CrossProduct.Z < 0) {
		Theta *= -1.f;
	}
	FName Section("From Back");

	if (Theta >= -45.f && Theta<45.f) {
		Section = FName("FromFront");
	}
	else if (Theta >= 45.f && Theta < 135.f) {
		Section = FName("FromRight");
	}
	else if (Theta >= -135.f && Theta < -45.f) {
		Section = FName("FromLeft");
	}


	/*if (GEngine) {
		GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Green, FString::Printf(TEXT("Theta:%f"), Theta));
	}*/
	PlayMotageHitReact(Section);
}

void AEnemy::PatroTimerFinished()
{
	MoveToTarget(PatrolTarget);
}

void AEnemy::PlayMotageHitReact(const FName SectionName)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && HitReactMontage) {
		AnimInstance->Montage_Play(HitReactMontage);
		AnimInstance->Montage_JumpToSection(SectionName, HitReactMontage);
	}
}



float AEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (Attributes&& HealthBarWidget) {
		Attributes->ReceveDamage(DamageAmount);
		HealthBarWidget->SetHealthPercent(Attributes->GetHealthPercent());

	}
	CombatTarget = DamageCauser;
	EnemyState = EEnemyState::EES_Chasing;
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	MoveToTarget(CombatTarget);
	return 0.0f;
}



