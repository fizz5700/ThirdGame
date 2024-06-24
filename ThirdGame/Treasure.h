// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Treasure.generated.h"

/**
 * 
 */
UCLASS()
class THIRDGAME_API ATreasure : public AItem
{
	GENERATED_BODY()
protected:	
	virtual void OnSphereOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
private:
	UPROPERTY(EditAnywhere, Category = "Sounds")
	USoundBase* PickUpSound;

	UPROPERTY(EditAnywhere, Category = "Treasure Properties")
	int32 Gold;
};
