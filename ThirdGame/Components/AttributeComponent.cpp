

#include "AttributeComponent.h"

UAttributeComponent::UAttributeComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	CureRemainTimes=MaxRemainTimes;
}



void UAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UAttributeComponent::ReceiveDamage(float Damage)
{
	Damage = Damage - defense - DamageReduction;
	if (Damage<0) {
		Damage = 0;
	}
	Health = FMath::Clamp(Health - Damage,0.f,MaxHealth);
}

void UAttributeComponent::Cure(float CureNum)
{
	//CureRemainTimes--;  在人物那边扣减剩余次数
	Health = FMath::Clamp(Health + CureNum, 0.f, MaxHealth);
}

void UAttributeComponent::UseStamina(float StaminaCost)
{
	Stamina = FMath::Clamp(Stamina - StaminaCost, 0.f, MaxStamina);
}


void UAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}


float UAttributeComponent::GetHealthPercent()
{
	return Health / MaxHealth;
}

float UAttributeComponent::GetStaminaPercent()
{
	return Stamina / MaxStamina;
}


float UAttributeComponent::GetMaxStamina()
{
	return MaxStamina;
}

bool UAttributeComponent::IsAlive()
{
	return Health>0.f;
}

void UAttributeComponent::SetMaxHealth(int32 MaxHealthNum)
{
	MaxHealth += MaxHealthNum;
}

void UAttributeComponent::SetMagicPower(int32 MagicPowerNum)
{
	MagicPower+= MagicPowerNum;
}

void UAttributeComponent::SetAttack(int32 attackNum)
{
	attack += attackNum;
}

void UAttributeComponent::SetCriticalHitRate(float CriticalHitRateNum)
{
	CriticalHitRate += CriticalHitRateNum;
}

void UAttributeComponent::SetCriticalDamage(float CriticalDamageNum)
{
	CriticalPercent += CriticalDamageNum;
}

void UAttributeComponent::SetDamageBonus(int32 DamageBonusNum)
{
	DamageBonus += DamageBonusNum;
}

void UAttributeComponent::SetDamageReduction(int32 DamageReductionNum)
{
	DamageReduction += DamageReductionNum;
}

void UAttributeComponent::SetDefense(int32 DefenseNum)
{
	defense += DefenseNum;
}

void UAttributeComponent::SetMaxStamina(int32 StaminaNum)
{
	MaxStamina += StaminaNum;
}

void UAttributeComponent::SetStaminaRegenRate(int32 StaminaRegenRateNum)
{
	StaminaRegenRate += StaminaRegenRateNum;
}

bool UAttributeComponent::UseCureTimes()
{
	{
		if (CureRemainTimes == 0) {
			return false;
		}
		CureRemainTimes--;
		return true;
	}
}

void UAttributeComponent::AddGold(int32 AmountOfGold)
{
	Gold += AmountOfGold;
}

void UAttributeComponent::AddSouls(int32 NumberOfSouls)
{
	Souls += NumberOfSouls;
}

void UAttributeComponent::RegenStamina(float DeltaTime)
{
	Stamina = FMath::Clamp(Stamina + StaminaRegenRate * DeltaTime, 0.f, MaxStamina);
}

void UAttributeComponent::ResetState()
{
	CureRemainTimes = MaxRemainTimes;
	Health = MaxHealth;
	Stamina = MaxStamina;
}
