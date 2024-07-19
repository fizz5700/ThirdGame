// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PickUpInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPickUpInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class THIRDGAME_API IPickUpInterface
{
	GENERATED_BODY()

	
public:
	//UFUNCTION(BlueprintNativeEvent)
	virtual void SetOverlappingItem(class AItem* Item);
	virtual void AddSoul(class ASoul* Soul);
};
