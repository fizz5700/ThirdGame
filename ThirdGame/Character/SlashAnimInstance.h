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

	UPROPERTY(BlueprintReadWrite)
	class ASlashCharacter* SlashCharacter;


	UPROPERTY(BlueprintReadWrite, Category = "MoveMent")
	class UCharacterMovementComponent* SlashCharacterMovement;

	UPROPERTY(BlueprintReadWrite, Category = "MoveMent")
	float GroundSpeed;
	UPROPERTY(BlueprintReadWrite, Category = "MoveMent")
	bool IsFalling;
	UPROPERTY(BlueprintReadWrite, Category = "MoveMent | Character State")
	ECharacterState CharacterState;

	UPROPERTY(BlueprintReadWrite, Category = Movement)
	EActionState ActionState;

	UPROPERTY(BlueprintReadWrite, Category = Movement)
	TEnumAsByte<EDeathPose> DeathPose;

};

