

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Interfaces/HitInterface.h"
#include "../Components/AttributeComponent.h"
#include "../HUD/HealthBarComponent.h"
#include "../Character/CharacterTypes.h"
#include "Enemy.generated.h"
class UAnimMontage;
class UAttributeComponent;
class UHealthBarComponent;
class UPawnSensingComponent;
UCLASS()
class THIRDGAME_API AEnemy : public ACharacter,public IHitInterface
{
	GENERATED_BODY()

public:
	AEnemy();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetHit_Implementation(const FVector& ImpactPoint) override;
	UFUNCTION()
	void MoveToTarget(AActor* Target);

	void DirectionalHitReact(const FVector& ImpactPoint);

	FTimerHandle PatroTimer;

	void PatroTimerFinished();

	/*
	*  Animation montages
	*/
	UFUNCTION(BlueprintCallable)
	void PlayMotageHitReact(const FName SectionName);

	UFUNCTION()
	void Die();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY()
	class AActor* CombatTarget;


	/**
	*Navigation
	*/
	UPROPERTY()
	class AAIController* EnemyController;

	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
	AActor* PatrolTarget;

	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
	TArray<AActor*> PatrolTargets;

protected:
	virtual void BeginPlay() override;	
	UPROPERTY(BlueprintReadOnly)
	EDeathPose DeathPose = EDeathPose::EDP_Alive;

	bool InTarGetRange(AActor* Target,double Radius);

	UPROPERTY(EditAnywhere)
	double PatrolRadius = 200.f;
	UFUNCTION()
	AActor* choosePatrolTarget();
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

	UPROPERTY(EditAnywhere)
	double CombarRadius = 500.f;
	
};
