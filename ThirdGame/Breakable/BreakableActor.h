
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interfaces/HitInterface.h"
#include "BreakableActor.generated.h"


class UGeometryCollectionComponent;
UCLASS()
class THIRDGAME_API ABreakableActor : public AActor,public IHitInterface
{
	GENERATED_BODY()
	
public:	
	ABreakableActor();
	virtual void Tick(float DeltaTime) override;

	virtual void GetHit_Implementation(const FVector& ImpactPoint) override;
protected:
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite)
	class UCapsuleComponent* Capsule;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite)
	UGeometryCollectionComponent* GeometryCollection;
private:	

	UPROPERTY(EditAnyWhere)
	TArray<TSubclassOf<class ATreasure>> TreasureClasses;

	bool bBroken = false;

};
