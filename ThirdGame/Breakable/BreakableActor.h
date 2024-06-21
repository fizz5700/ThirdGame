
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

private:	
	UPROPERTY(VisibleAnyWhere)
	UGeometryCollectionComponent* GeometryCollection;

	UPROPERTY(EditAnyWhere)
	UClass* TreasureClass;

};
