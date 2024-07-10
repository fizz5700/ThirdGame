
#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "CharacterTypes.h"
#include "SlashCharacter.generated.h"
class AItem;
class UAnimMontage;

UCLASS()
class THIRDGAME_API ASlashCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	ASlashCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

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
protected:
	virtual void BeginPlay() override;
	
	virtual void AttackEnd() override;

	UFUNCTION(BlueprintCallable)
	virtual void FinishArm();
private:

	UPROPERTY(VisibleInstanceOnly)
	AItem* OverlappingItem;

	UPROPERTY(EditDefaultsOnly, Category = "Montage")
	UAnimMontage* EquipMontage;

public:
	FORCEINLINE void SetOverlappingItem(AItem* Item) {
		OverlappingItem = Item;
	}
	
	FORCEINLINE ECharacterState GetCharacterState() const{
		return CharacterState;
	}


};
