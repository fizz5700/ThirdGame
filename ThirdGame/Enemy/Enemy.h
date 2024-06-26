

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Interfaces/HitInterface.h"
#include "../Components/AttributeComponent.h"
#include "../HUD/HealthBarComponent.h"
#include "Enemy.generated.h"
class UAnimMontage;
class UAttributeComponent;
class UHealthBarComponent;

UCLASS()
class THIRDGAME_API AEnemy : public ACharacter,public IHitInterface
{
	GENERATED_BODY()

public:
	AEnemy();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetHit_Implementation(const FVector& ImpactPoint) override;

	void DirectionalHitReact(const FVector& ImpactPoint);

	/*
	*  Animation montages
	*/
	UFUNCTION(BlueprintCallable)
	void PlayMotageHitReact(const FName SectionName);

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	

protected:
	virtual void BeginPlay() override;	

private:
	/*
	*  Animation montages
	*/
	UPROPERTY(EditDefaultsOnly, Category = "Montage")
	UAnimMontage* HitReactMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montage")
	UAnimMontage* DeathMontage;

	UPROPERTY(EditAnywhere, Category = "Sounds")
	USoundBase* HitSound;
	UPROPERTY(EditAnywhere, Category = "Sounds")
	UParticleSystem* HitParticles;

	UPROPERTY(EditAnywhere)
	UAttributeComponent* Attributes;

	UPROPERTY(EditAnywhere)
	UHealthBarComponent* HealthBarWidget;
};
