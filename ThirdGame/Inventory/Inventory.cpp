#include "Inventory.h"  
#include "CoreMinimal.h"
#include "ThirdGame/Character/CharacterTypes.h"

void FInventory::AddItem(FString ItemName, int Quantity, EItemType ItemType)
{
  // for (auto& Item : Items)
  // {
  //     if (Item.Name == ItemName)
  //     {
  //         Item.Quantity += Quantity;
  //         return;
  //     }
  // }
  // Items.emplace_back(ItemName, Quantity);
}

void FInventory::RemoveItem(FString ItemName, int Quantity, EItemType ItemType)
{
   //for (auto& Item : Items)
   //{
   //    if (Item.Name == ItemName)
   //    {
   //        if (Item.Quantity >= Quantity)
   //        {
   //            Item.Quantity -= Quantity;
   //            if (Item.Quantity <= 0)
   //            {
   //                //Items.erase(std::remove(Items.begin(), Items.end(), Item), Items.end());
   //            }
   //            return;
   //        }
   //    }
   //}
}

bool FInventory::HasItem(FString ItemName, int Quantity, EItemType ItemType)
{
  // for (const auto& Item : Items)
  // {
  //     if (Item.Name == ItemName && Item.Quantity >= Quantity)
  //     {
          return true;
  //     }
  // }
  // return false;
}