// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterTypes.h"
#include "SlashAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class THIRDGAME_API USlashAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DetalTime) override;

	UPROPERTY(BlueprintReadOnly)
	class ASlashCharacter* SlashCharacter;


	UPROPERTY(BlueprintReadOnly, Category = "MoveMent")
	class UCharacterMovementComponent* SlashCharacterMovement;

	UPROPERTY(BlueprintReadOnly, Category = "MoveMent")
	float GroundSpeed;
	UPROPERTY(BlueprintReadOnly, Category = "MoveMent")
	bool IsFalling;
	UPROPERTY(BlueprintReadOnly, Category = "MoveMent | Character State")
	ECharacterState CharacterState;

};

