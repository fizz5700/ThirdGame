
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ThirdGame/Item.h"
#include "UInventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THIRDGAME_API UUInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UUInventoryComponent();

protected:
	virtual void BeginPlay() override;


	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    using InventorySlot = TSubclassOf<class UItem>;
  
    //UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
   // TArray<InventorySlot> InventorySlots;

   // UFUNCTION(BlueprintCallable, Category = "Inventory")
    //void AddItem(TSubclassOf<class UItem> ItemClass);

    // Additional functions for removing items, checking inventory, etc.  

public:

};
