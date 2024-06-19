

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Interfaces/HitInterface.h"
#include "Enemy.generated.h"
class UAnimMontage;
UCLASS()
class THIRDGAME_API AEnemy : public ACharacter,public IHitInterface
{
	GENERATED_BODY()

public:
	AEnemy();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetHit(const FVector& ImpactPoint) override;

	void DirectionalHitReact(const FVector& ImpactPoint);

	/*
	*  Animation montages
	*/
	UFUNCTION(BlueprintCallable)
	void PlayMotageHitReact(const FName SectionName);
protected:
	virtual void BeginPlay() override;	


	/*
	*  Animation montages
	*/
	UPROPERTY(EditDefaultsOnly, Category = "Montage")
	UAnimMontage* HitReactMontage;


};
