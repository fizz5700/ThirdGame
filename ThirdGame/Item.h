
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"
class UCapsuleComponent; 
class USphereComponent;
class UBoxComponent;

enum class EItemState : int8 {
	EIS_Hovering,
	EIS_Equipped
};

UCLASS()
class THIRDGAME_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AItem();
	virtual void Tick(float DeltaTime) override;

	
	UFUNCTION()
	virtual void OnSphereOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    
	UFUNCTION()
	virtual void OnSphereEndOverlap(class UPrimitiveComponent* OnComponentEndOverlap, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32  OtherBodyIndex);

	virtual void PickUpSystem();

	virtual void PickUpSound();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintPure)
	float TransformedSin();

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UStaticMeshComponent* ItemMesh;

	EItemState ItemState = EItemState::EIS_Hovering;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sine Parameters")
	float Amplitude = 0.25f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sine Parameters")
	float TimeConstant = 5.f;
	UPROPERTY(VisibleAnywhere)
	USphereComponent* Sphere;

	UPROPERTY(EditAnywhere)
	class UNiagaraComponent* ItemEffect;

	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* PcikUpEffect;

	UPROPERTY(EditAnywhere)
	class USoundBase* PcikUpSound;
private:
	

	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* Capsule;

	

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* MyBoxComponent;

	float RunningTime;

	
};
