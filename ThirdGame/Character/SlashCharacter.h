
#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "CharacterTypes.h"
#include "InputActionValue.h"
#include "ThirdGame/Inventory/UInventoryComponent.h"
#include "SlashCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UGroomComponent;
class AItem;
class ASoul;
class ATreasure;
class UAnimMontage;
class USlashOverlay;
class UInventoryComponent;

UCLASS(Config = Game)
class THIRDGAME_API ASlashCharacter : public ABaseCharacter, public IPickUpInterface
{
	GENERATED_BODY()

public:

	ASlashCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter) override;

	void Dodge();

	UFUNCTION(BlueprintCallable)
	bool HasEnoughStamina(float StaminaCost);

	bool IsOccupied();

	virtual void DodgeEnd() override;

	UFUNCTION(BlueprintCallable)
	void EKeyPressed();

	UFUNCTION(BlueprintCallable)
	void SpawnWindWall();
	UFUNCTION(BlueprintCallable)
	void SendFlyObject();


	bool CanDisarm();

	bool CanArm();

	virtual void Attack() override;

	UFUNCTION(BlueprintCallable)
	void ReleaseSkills();

	bool CanAttack();

	UFUNCTION()
	void PlayEquipMontage(FName SectionName);

	UFUNCTION(BlueprintCallable)
	void PlayCureMontage(FName SectionName);

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

	virtual void AddSouls(class ASoul* Soul) override;

	virtual void AddGold(class ATreasure* Treasure) override;
	
	UFUNCTION(BlueprintCallable)
	bool ReduceCureTimes();
protected:
	UFUNCTION()
	void Move(const FInputActionValue& Value);
	UFUNCTION()
	void Look(const FInputActionValue& Value);

	virtual void BeginPlay() override;

	virtual void AttackEnd() override;

	UFUNCTION(BlueprintCallable)
	virtual void FinishArm(); 

	UFUNCTION(BlueprintCallable)
	void HitReactEnd();

	virtual void Die() override;

	void ReSpawn();
	void DisableMeshCollision();

	FTimerHandle ReSpawnTimer;
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input")
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input")
	class UCameraComponent* FollowCamera;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* JumpAction;
	
	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* DodgeAction;

	UPROPERTY(BlueprintReadOnly, BlueprintReadOnly, Category = "Inventory")
	UInventoryComponent* InventoryComponent;

	UPROPERTY(BlueprintReadWrite)
	FTransform NearestReSpawn;

	UPROPERTY(BlueprintReadWrite)
	FVector NearestReSpawnVector;

private:

	UPROPERTY()
	USlashOverlay* SlashOverlay;

	UPROPERTY(EditDefaultsOnly, Category = "Montage")
	UAnimMontage* EquipMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montage")
	UAnimMontage* CureMontage;

	UPROPERTY(VisibleAnywhere, Category = "Hair")
	UGroomComponent* Hair;

	UPROPERTY(VisibleAnywhere, Category = "Hair")
	UGroomComponent* Eyebrows;

	void InitializeSlashOverlay();

	UFUNCTION(BlueprintCallable)
	void SetHUDHealth();
public:

	/** Getter and Setter for the InventoryComponent */
	UFUNCTION(BlueprintCallable)
	UInventoryComponent* GetInventoryComponent() const { return InventoryComponent; }

	UFUNCTION(BlueprintCallable)
	void SetInventoryComponent(UInventoryComponent* NewInventoryComponent) { InventoryComponent = NewInventoryComponent; }

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	AItem* OverlappingItem;

	UPROPERTY(EditAnywhere, Category = Combat)
	TSubclassOf<class AWindWall> WindWallClass;

	UPROPERTY(EditAnywhere, Category = Combat)
	TSubclassOf<class AFlyObject> FlyObjectClass;

	FORCEINLINE ECharacterState GetCharacterState() const{
		return CharacterState;
	}

	FORCEINLINE EActionState GetActionState() const { return ActionState; }

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
