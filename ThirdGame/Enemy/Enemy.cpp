

#include "Enemy.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
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

}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::GetHit_Implementation(const FVector& ImpactPoint)
{
	//if (GetWorld()) DrawDebugSphere(GetWorld(), ImpactPoint, 8.f, 12, FColor::Red, false,5.f);
	
	if (Attributes&& Attributes->IsAlive()) {
		DirectionalHitReact(ImpactPoint);
	}
	else
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance && DeathMontage) {
			AnimInstance->Montage_Play(DeathMontage);
			const int32 Selection = FMath::RandRange(0, 5);
			FName SectionName = FName();
			switch (Selection) {
			case 0:
				SectionName = FName("Death1");
				break;
			case 1:
				SectionName = FName("Death2");
				break;
			case 2:
				SectionName = FName("Death3");
				break;
			case 3:
				SectionName = FName("Death4");
				break;
			case 4:
				SectionName = FName("Death5");
				break;
			case 5:
				SectionName = FName("Death6");
				break;
			default:
				break;
			}
			AnimInstance->Montage_JumpToSection(SectionName, HitReactMontage);
		}
	}
		

	if (HitSound) {
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, ImpactPoint);
	}

	if (HitParticles&& GetWorld()) {
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticles, ImpactPoint);
	}

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
	return 0.0f;
}



