// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ThirdGame/Item.h"
#include "WindWall.generated.h"

/**
 * 
 */
UCLASS()
class THIRDGAME_API AWindWall : public AItem
{
	GENERATED_BODY()
public:
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
	void LifeSpanExpired();
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
private:

	double DesiredX;

	UPROPERTY(EditAnywhere)
	float DriftRate = 15.f;

	UPROPERTY(EditAnywhere, Category = Combat)
	float InLifeSpan = 8.f;
public:

};
