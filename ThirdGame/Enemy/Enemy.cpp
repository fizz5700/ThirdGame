

#include "Enemy.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Animation/AnimMontage.h"
//#include "Slash/DebugMacros.h"
AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility,ECollisionResponse::ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	
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

void AEnemy::GetHit(const FVector& ImpactPoint)
{
	if (GetWorld()) DrawDebugSphere(GetWorld(), ImpactPoint, 8.f, 12, FColor::Red, false,5.f);
	DirectionalHitReact(ImpactPoint);
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


	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Green, FString::Printf(TEXT("Theta:%f"), Theta));
	}
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

