// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ThirdGame/Item.h"
#include "FlyObject.generated.h"

/**
 * 
 */
UCLASS()
class THIRDGAME_API AFlyObject : public AItem
{
	GENERATED_BODY()
public:
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
	void LifeSpanExpired();
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	void ExcuteGetHit(AActor* OtherActor);
private:

	double DesiredX;

	UPROPERTY(EditAnywhere)
	float DriftRate = 500.f;

	UPROPERTY(EditAnywhere, Category = Combat)
	float InLifeSpan = 8.f;

	UPROPERTY(EditAnywhere, Category = Combat)
	float Damage = 20.f;

	UPROPERTY(EditAnywhere, Category = Combat)
	float StaminaCost = 20.f;
public:
	FORCEINLINE float GetStaminaCost() const { return StaminaCost; }
	void setDamage(float MagicPower);
};
