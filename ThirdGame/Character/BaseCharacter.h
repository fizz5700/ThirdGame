
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Interfaces/HitInterface.h"
#include "CharacterTypes.h"
#include "BaseCharacter.generated.h"

class AWeapon;
class UAttributeComponent;
class UAnimMontage;
UCLASS()
class THIRDGAME_API ABaseCharacter : public ACharacter, public IHitInterface
{
	GENERATED_BODY()

public:
	
	ABaseCharacter();

	virtual void Tick(float DeltaTime) override;
	/*
	*  slash
	*/
	UFUNCTION(BlueprintCallable)
	void EnableWeaponCollision(ECollisionEnabled::Type CollisionEnabled);

	


	/*
	*  enemy
	*/

	 void GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter) override;

	bool IsAlive();

	void PlayHitSound(const FVector& ImpactPoint);

	void SpawnHitParticles(const FVector& ImpactPoint);

	void DirectionalHitReact(const FVector& ImpactPoint);

	/*
	*  Animation montages
	*/
	UFUNCTION(BlueprintCallable)
	void PlayMotageHitReact(const FName SectionName);

	UFUNCTION()
	virtual void Die();

 protected:
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	virtual void Attack();

	UFUNCTION(BlueprintCallable)
	virtual void AttackEnd();

	int32 PlayRandomMontageSection(UAnimMontage* Montage, const TArray<FName>& SectionNames);

	void DisableCapsule();

	virtual bool CanAttack();

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	AWeapon* EquippedWeapon;
	
	UPROPERTY(EditAnywhere)
	UAttributeComponent* Attributes;
	/*
   *  Animation montages
   */


	UPROPERTY(EditAnywhere, Category = Combat)
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere, Category = Combat)
	UParticleSystem* HitParticles;

	UPROPERTY(EditDefaultsOnly, Category = Combat)
	UAnimMontage* AttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = Combat)
	UAnimMontage* HitReactMontage;

	UPROPERTY(EditDefaultsOnly, Category = Combat)
	UAnimMontage* DeathMontage;

	UPROPERTY(BlueprintReadOnly, Category = Combat)
	AActor* CombatTarget;

	//UPROPERTY(EditDefaultsOnly, Category = Combat)
	//UAnimMontage* DodgeMontage;

	UPROPERTY(EditAnywhere, Category = Combat)
	TArray<FName> AttackMontageSections;

	UPROPERTY(EditAnywhere, Category = Combat)
	TArray<FName> DeathMontageSections;

	virtual void HandleDamage(float DamageAmount);

	void SetWeaponCollisionEnabled(ECollisionEnabled::Type CollisionEnabled);

	void StopAttackMontage();

	void PlayMontageSection(UAnimMontage* Montage, const FName& SectionName);

	virtual int32 PlayDeathMontage();
	
	virtual int32 PlayAttackMontage();


	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<EDeathPose> DeathPose;

private:
	
	
};
