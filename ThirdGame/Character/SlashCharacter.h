
#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "CharacterTypes.h"
#include "SlashCharacter.generated.h"
class USpringArmComponent;
class UCameraComponent;
class UGroomComponent;
class AItem;
class ASoul;
class ATreasure;
class UAnimMontage;
class USlashOverlay;

UCLASS()
class THIRDGAME_API ASlashCharacter : public ABaseCharacter, public IPickUpInterface
{
	GENERATED_BODY()

public:
	ASlashCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter) override;

	UFUNCTION(BlueprintCallable)
	void EKeyPressed();

	bool CanDisarm();

	bool CanArm();

	virtual void Attack() override;

	bool CanAttack();

	UFUNCTION()
	void PlayEquipMontage(FName SectionName);

	UPROPERTY(EditAnywhere)
	ECharacterState CharacterState = ECharacterState::ECS_Unequipped;
	UPROPERTY(BlueprintReadWrite)
	EActionState ActionState = EActionState::EAS_Unoccupied;


	UFUNCTION(BlueprintCallable)
	void DisArm();
	
	UFUNCTION(BlueprintCallable)
	void Arm();

	

	UFUNCTION(BlueprintCallable)
	void DisableWeaponCollision(ECollisionEnabled::Type CollisionDisabled);

	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	virtual void SetOverlappingItem(class AItem* Item) override;

	virtual void AddSoul(class ASoul* Soul) override;
protected:
	virtual void BeginPlay() override;

	

	UFUNCTION(BlueprintCallable)
	void AttackEnd();

	UFUNCTION(BlueprintCallable)
	virtual void FinishArm();

	UFUNCTION(BlueprintCallable)
	void HitReactEnd();

	virtual void Die() override;
	void DisableMeshCollision();
private:

	UPROPERTY()
	USlashOverlay* SlashOverlay;

	UPROPERTY(VisibleInstanceOnly)
	AItem* OverlappingItem;

	UPROPERTY(EditDefaultsOnly, Category = "Montage")
	UAnimMontage* EquipMontage;

	/** Character components */

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* ViewCamera;

	UPROPERTY(VisibleAnywhere, Category = "Hair")
	UGroomComponent* Hair;

	UPROPERTY(VisibleAnywhere, Category = "Hair")
	UGroomComponent* Eyebrows;

	void InitializeSlashOverlay();

	void SetHUDHealth();
public:
	//FORCEINLINE void SetOverlappingItem(AItem* Item) {
	//	OverlappingItem = Item;
	//}
	
	FORCEINLINE ECharacterState GetCharacterState() const{
		return CharacterState;
	}

	FORCEINLINE EActionState GetActionState() const { return ActionState; }

	
};
