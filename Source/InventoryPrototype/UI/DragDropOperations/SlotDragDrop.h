// InventoryPrototype / Fedosov Vladislav

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "SlotDragDrop.generated.h"

UCLASS()
class INVENTORYPROTOTYPE_API USlotDragDrop : public UDragDropOperation
{
	GENERATED_BODY()

public:
	void SetIndex(int32 NewIndex) { Index = NewIndex; }
	int32 GetIndex() const { return Index; }

private:
	int32 Index;
};
