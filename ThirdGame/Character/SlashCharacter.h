
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterTypes.h"
#include "SlashCharacter.generated.h"
class AItem;
class UAnimMontage;
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

	UPROPERTY(EditAnywhere)
	ECharacterState CharacterState = ECharacterState::ECS_Unequipped;
	

protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleInstanceOnly)
	AItem* OverlappingItem;
	
    /*
	*  Animation montages
	*/
	UPROPERTY(EditDefaultsOnly, Category = "Montage")
	UAnimMontage* Attackmontage;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess="true"))
	EActionState ActionState = EActionState::EAS_Unoccupied;

public:
	FORCEINLINE void SetOverlappingItem(AItem* Item) {
		OverlappingItem = Item;
	}
	
	FORCEINLINE ECharacterState GetCharacterState() const{
		return CharacterState;
	}


};
