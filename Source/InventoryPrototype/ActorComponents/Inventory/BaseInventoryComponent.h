// InventoryPrototype / Fedosov Vladislav

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DataTypes.h"
#include "BaseInventoryComponent.generated.h"

struct FItemProperties;

DECLARE_MULTICAST_DELEGATE(FOnInventoryUpdated);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class INVENTORYPROTOTYPE_API UBaseInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBaseInventoryComponent();
	TArray<FItemData> GetInventory() const { return Inventory; }
	FItemProperties* GetItemProperties(EItemID ID) const;
	void TransferSlots(int32 SourceIndex, int32 DestinationIndex);
	void SplitSlot(int32 SourceIndex, int32 DestinationIndex, int32 AmountToSplit);
	FOnInventoryUpdated OnInventoryUpdated;
	int32 GetMaxStackSize(EItemID ID) const;
	void DropItem(int32 Index);

protected:
	void IncreaseStack(const int32 Index,const int32 Amount);
	void IncreaseStack(FItemData& InventorySlot,const int32 Amount);
	void DecreaseStack(const int32 Index,const int32 Amount);
	void DecreaseStack(FItemData& InventorySlot, const int32 Amount);
	void MakeSlotNone(const int32 Index);
	bool SpawnItemToDrop(int32 AmountToDrop, FItemProperties* ItemProperties);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item: Properties")
	FString ItemDataTableReference;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory: Properties")
	int32 InventoryCapacity = 12;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory: Properties")
	TArray<FItemData> Inventory;
};
