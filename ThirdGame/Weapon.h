
#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Weapon.generated.h"

class USoundBase;
class UBoxComponent;
class UNiagaraComponent;
UCLASS()
class THIRDGAME_API AWeapon : public AItem
{
	GENERATED_BODY()
	
protected:
	void BeginPlay() override;
	virtual void OnSphereOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnSphereEndOverlap(class UPrimitiveComponent* OnComponentEndOverlap, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32  OtherBodyIndex) override;

	UFUNCTION()
	void OnBoxOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintImplementableEvent)
	void CreateFields(const FVector& FieldLocation);
public:
	AWeapon();
	void Equip(USceneComponent* InParent, FName InSocketName);
	void AttachMeshToSocket(USceneComponent* InParent, const FName& InSocketName);
private:
	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	USoundBase* EquipSound;
	UPROPERTY(VisibleAnywhere, Category = "Weapon Properties")
	UBoxComponent* WeaponBox;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* BoxTraceStart;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* BoxTraceEnd;

	
public:
	FORCEINLINE UBoxComponent* GetWeaponBox() const {
		return WeaponBox;
	}
	TArray<AActor*> IgnoreActors;
};
