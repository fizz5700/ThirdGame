// Inventory.h  
#pragma once  

#include "CoreMinimal.h"
#include <vector>  

 class FInventoryItem
{
public:
    FString Name;
    int Quantity;
    EItemType ItemType;
    FInventoryItem(FString InName, int InQuantity, EItemType InItemType)
        : Name(InName), Quantity(InQuantity), ItemType(InItemType)
    {
    }
};

class FInventory
{
public:
    std::vector<FInventoryItem> Items;

    void AddItem(FString ItemName, int Quantity, EItemType ItemType);
    void RemoveItem(FString ItemName, int Quantity, EItemType ItemType);
    bool HasItem(FString ItemName, int Quantity, EItemType ItemType);
};