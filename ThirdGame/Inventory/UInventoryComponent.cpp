
#include "ThirdGame/Inventory/UInventoryComponent.h"


UUInventoryComponent::UUInventoryComponent()
{

	PrimaryComponentTick.bCanEverTick = true;


}


void UUInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

}


void UUInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

//void UUInventoryComponent::AddItem(TSubclassOf<class UItem> ItemClass)
//{
//}

