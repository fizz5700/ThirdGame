
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterTypes.h"
#include "SlashCharacter.generated.h"
class AItem;
class UAnimMontage;
class AWeapon;
UCLASS()
class THIRDGAME_API ASlashCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASlashCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void EKeyPressed();

	UFUNCTION(BlueprintCallable)
	void Attack();

	UFUNCTION()
	void PlayAttackMontage();

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
	void EnableWeaponCollision(ECollisionEnabled::Type CollisionEnabled);

	UFUNCTION(BlueprintCallable)
	void DisableWeaponCollision(ECollisionEnabled::Type CollisionDisabled);
protected:
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	virtual void AttackEnd();

	UFUNCTION(BlueprintCallable)
	virtual void FinishArm();
private:

	UPROPERTY(VisibleInstanceOnly)
	AItem* OverlappingItem;
	
    /*
	*  Animation montages
	*/
	UPROPERTY(EditDefaultsOnly, Category = "Montage")
	UAnimMontage* AttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montage")
	UAnimMontage* EquipMontage;

	
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	AWeapon* EquippedWeapon;

public:
	FORCEINLINE void SetOverlappingItem(AItem* Item) {
		OverlappingItem = Item;
	}
	
	FORCEINLINE ECharacterState GetCharacterState() const{
		return CharacterState;
	}


};
