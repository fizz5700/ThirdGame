
#pragma once
//USTRUCT(BlueprintType)  // ����Ϊ��ͼ����
//struct FInventoryItem : public FTableRowBase {
//	GENERATED_BODY();
//
//public:
//
//	FInventoryItem() { // ���캯�� �������г�ʼ����
//		Name = FText::FromString("Item");
//		Action = FText::FromString("Use");
//		Description = FText::FromString("Please enter a description for this item");
//		Value = 10;
//	}
//
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	FName ItemID;  // ��Ʒ��ID
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	TSubclassOf<class Apickup> Itempickup; // ʰȡ���Ͷ���
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	FText Name; // ��������
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	FText Action; // ��������
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	int32 Value;  // �����ֵ
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	UTexture2D* Thumbnail; // �������ͼƬ��Ϣ
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	FText Description; // �Ը����ݵ�����
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	TArray<FCraftingInfo> CraftCombinations; // ��������໥�ںϵ���Ʒ��Ϣ
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	bool bCanBeUsed; // �Ƿ���Ա�ʹ��
//
//	bool operator == (const FInventoryItem& Item) const { // ���ص��ںţ��������ID��ͬ����˵����������������ͬһ�����͡�
//		if (ItemID == Item.ItemID) return true;
//		else return false;
//	}
//};