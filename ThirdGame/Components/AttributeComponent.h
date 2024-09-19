
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class THIRDGAME_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAttributeComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float Health;

	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float MaxHealth;

	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float Stamina;

	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float MaxStamina;

	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	int32 Souls;

	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	int32 Gold;

	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float DodgeCost = 14.f;

	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float StaminaRegenRate = 2.f;

	//Ê£Óà¾Æºø´ÎÊý
	UPROPERTY(EditAnywhere, Category = "Cure Attributes")
	int32 CureRemainTimes;

	//×î´ó¾Æºø´ÎÊý
	UPROPERTY(EditAnywhere, Category = "Cure Attributes")
	int32 MaxRemainTimes = 5;

	//·¨Á¦
	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	int32 MagicPower=0;

	//¹¥»÷Á¦
	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	int32 attack=20;

	//·ÀÓùÁ¦
	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	int32 defense=5;

	//±©»÷ÂÊ
	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float CriticalHitRate=0.02f;

	//±©»÷ÉËº¦
	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float CriticalPercent=1.5f;

	//ÉËº¦¼Ó³É
	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	int32 DamageBonus=0;

	//ÉËº¦¼õÃâ
	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	int32 DamageReduction=0;
public:
	UFUNCTION(BlueprintCallable)
	void ReceiveDamage(float Damage);

	UFUNCTION(BlueprintCallable)
	void Cure(float CureNum);

	UFUNCTION(BlueprintCallable)
	void UseStamina(float StaminaCost);

	UFUNCTION(BlueprintCallable)
	float GetHealthPercent();

	UFUNCTION(BlueprintCallable)
	float GetStaminaPercent();

	UFUNCTION(BlueprintCallable)
	float GetMaxStamina();

	UFUNCTION(BlueprintCallable)
	bool IsAlive();

	FORCEINLINE int32 GetGold() const { return Gold; }
	FORCEINLINE int32 GetSouls() const { return Souls; }
	FORCEINLINE int32 GetCureRemainTimes() const { return CureRemainTimes; }
	FORCEINLINE float GetDodgeCost() const { return DodgeCost; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE int32 GetMaxHealth() const { return MaxHealth; }
	UFUNCTION(BlueprintCallable)
	FORCEINLINE int32 GetMagicPower() const { return MagicPower; }
	UFUNCTION(BlueprintCallable)
	FORCEINLINE int32 GetAttack() const { return attack; }
	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetCriticalHitRate() const { return CriticalHitRate; }
	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetCriticalDamage() const { return CriticalPercent; }
	UFUNCTION(BlueprintCallable)
	FORCEINLINE int32 GetDamageBonus() const { return DamageBonus; }
	UFUNCTION(BlueprintCallable)
	FORCEINLINE int32 GetDamageReduction() const { return DamageReduction; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetStamina() const { return Stamina; }
	UFUNCTION(BlueprintCallable)
	FORCEINLINE int32 GetDefense() const { return defense; }
	UFUNCTION(BlueprintCallable)
	FORCEINLINE int32 GetStaminaRegenRate() const { return StaminaRegenRate; }
	

	UFUNCTION(BlueprintCallable)
	void SetMaxHealth(int32 MaxHealthNum);
	UFUNCTION(BlueprintCallable)
	void SetMagicPower(int32 MagicPowerNum);
	UFUNCTION(BlueprintCallable)
	void SetAttack(int32 attackNum);
	UFUNCTION(BlueprintCallable)
	void SetCriticalHitRate(float CriticalHitRateNum);
	UFUNCTION(BlueprintCallable)
	void SetCriticalDamage(float CriticalDamageNum);
	UFUNCTION(BlueprintCallable)
	void SetDamageBonus(int32 DamageBonusNum);
	UFUNCTION(BlueprintCallable)
	void SetDamageReduction(int32 DamageReductionNum);
	
	UFUNCTION(BlueprintCallable)
	void SetDefense(int32 DefenseNum);
	UFUNCTION(BlueprintCallable)
	void SetMaxStamina(int32 StaminaNum);
	UFUNCTION(BlueprintCallable)
	void SetStaminaRegenRate(int32 StaminaRegenRateNum);


	UFUNCTION()
	bool UseCureTimes();
	void AddGold(int32 AmountOfGold);

	void AddSouls(int32 NumberOfSouls);

	void RegenStamina(float DeltaTime);

	void ResetState();
};