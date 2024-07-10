

#pragma once

#include "CoreMinimal.h"
#include "../Interfaces/HitInterface.h"
#include "../HUD/HealthBarComponent.h"
#include "../Character/CharacterTypes.h"
#include "../Character/BaseCharacter.h"
#include "Enemy.generated.h"

class UHealthBarComponent;
class UPawnSensingComponent;
UCLASS()
class THIRDGAME_API AEnemy : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AEnemy();

	virtual void Tick(float DeltaTime) override;

	void CheckPartroTarget();


	virtual void GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter) override;

	FTimerHandle PatroTimer;

	void PatroTimerFinished();
	
	virtual void Die() override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	/**
	*Navigation
	*/
	UPROPERTY()
	class AAIController* EnemyController;

	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
	AActor* PatrolTarget;

	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
	TArray<AActor*> PatrolTargets;

	virtual void Destroyed() override;
	UPROPERTY(EditAnywhere)
	double PatrolRadius = 200.f;
protected:
	/**
	*Components
	*/
	UPROPERTY(VisibleAnywhere)
	UPawnSensingComponent* PawnSensing;

	virtual void BeginPlay() override;	

	UPROPERTY(EditAnywhere)
	EEnemyState EnemyState = EEnemyState::EES_Patrolling;

	bool InTarGetRange(AActor* Target,double Radius);

	UPROPERTY(EditAnywhere)
	double AcceptanceRadius = 50.f;
	UFUNCTION()
	AActor* choosePatrolTarget();

	UFUNCTION()
	void PawnSeen(APawn* SeenPawn);

	virtual void Attack() override;
	
private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AWeapon> WeaponClass;

	UPROPERTY(EditAnywhere)
	UHealthBarComponent* HealthBarWidget;

	UPROPERTY(EditAnywhere)
	double CombarRadius = 500.f;

	UPROPERTY(EditAnywhere)
	double AttackRadius = 150.f;

	/** AI Behavior */
	void InitializeEnemy();
	void CheckPatrolTarget();
	void CheckCombatTarget();
	bool CanAttack() override;
	void PatrolTimerFinished();
	void HideHealthBar();
	void ShowHealthBar();
	void LoseInterest();
	void StartPatrolling();
	void ChaseTarget();
	bool IsOutsideCombatRadius();
	bool IsOutsideAttackRadius();
	bool IsInsideAttackRadius();
	bool IsChasing();
	bool IsAttacking();
	bool IsDead();
	bool IsEngaged();
	virtual void AttackEnd() override;
	void ClearPatrolTimer();
	void StartAttackTimer();
	void ClearAttackTimer();
	bool InTargetRange(AActor* Target, double Radius);
	void MoveToTarget(AActor* Target);
	AActor* ChoosePatrolTarget();
	void SpawnDefaultWeapon();

	virtual int32 PlayDeathMontage() override;

	void HandleDamage(float DamageAmount);

	FTimerHandle PatrolTimer;

	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	float PatrolWaitMin = 5.f;

	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	float PatrolWaitMax = 10.f;

	UPROPERTY(EditAnywhere, Category = Combat)
	float PatrollingSpeed = 125.f;

	FTimerHandle AttackTimer;

	UPROPERTY(EditAnywhere, Category = Combat)
	float AttackMin = 0.5f;

	UPROPERTY(EditAnywhere, Category = Combat)
	float AttackMax = 1.f;

	UPROPERTY(EditAnywhere, Category = Combat)
	float ChasingSpeed = 300.f;

	UPROPERTY(EditAnywhere, Category = Combat)
	float DeathLifeSpan = 8.f;

	UPROPERTY(EditAnywhere, Category = Combat)
	double CombatRadius = 500.f;

};
