// InventoryPrototype / Fedosov Vladislav

#pragma once

#include "CoreMinimal.h"
#include "ActorComponents/Inventory/BaseInventoryComponent.h"
#include "PawnInventoryComponent.generated.h"

UCLASS()
class INVENTORYPROTOTYPE_API UPawnInventoryComponent : public UBaseInventoryComponent
{
	GENERATED_BODY()

public:
	void AddToInventory(AInteractableItemBase* InterItem);

protected:
	virtual void BeginPlay() override;
	int32 FindEmptySlot() const;
};
