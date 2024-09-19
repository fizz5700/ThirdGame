
#pragma once
//USTRUCT(BlueprintType)  // 声明为蓝图类型
//struct FInventoryItem : public FTableRowBase {
//	GENERATED_BODY();
//
//public:
//
//	FInventoryItem() { // 构造函数 变量进行初始化。
//		Name = FText::FromString("Item");
//		Action = FText::FromString("Use");
//		Description = FText::FromString("Please enter a description for this item");
//		Value = 10;
//	}
//
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	FName ItemID;  // 物品的ID
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	TSubclassOf<class Apickup> Itempickup; // 拾取类型对象
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	FText Name; // 对象名字
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	FText Action; // 对象作用
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	int32 Value;  // 对象的值
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	UTexture2D* Thumbnail; // 储存对象图片信息
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	FText Description; // 对该数据的描述
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	TArray<FCraftingInfo> CraftCombinations; // 储存可以相互融合的物品信息
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	bool bCanBeUsed; // 是否可以被使用
//
//	bool operator == (const FInventoryItem& Item) const { // 重载等于号，如果他们ID相同，就说明他们两个是属于同一种类型。
//		if (ItemID == Item.ItemID) return true;
//		else return false;
//	}
//};