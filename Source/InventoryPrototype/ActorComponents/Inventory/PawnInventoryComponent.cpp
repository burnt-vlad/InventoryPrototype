// InventoryPrototype / Fedosov Vladislav

#include "ActorComponents/Inventory/PawnInventoryComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Actors/Items/InteractableItemBase.h"

void UPawnInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPawnInventoryComponent::AddToInventory(AInteractableItemBase* InterItem)
{
	// Check if the InterItem is valid and has a valid ID and amount
	if (!InterItem || InterItem->GetID() == EItemID::None || InterItem->GetAmount() <= 0) return;
	const int32 InterItemStackSize = GetMaxStackSize(InterItem->GetID());

	const EItemID InterItemID = InterItem->GetID();

	for (auto& Slot : Inventory)
	{
		// Iterate through the inventory to find matching items
		if (Slot.ID == InterItemID)
		{
			const int32 SlotEmptySize = GetMaxStackSize(Slot.ID) - Slot.Amount;
			if (SlotEmptySize >= InterItem->GetAmount())   
			{ 
				IncreaseStack(Slot, InterItem->GetAmount());
				InterItem->Destroy();
				OnInventoryUpdated.Broadcast();
				return;
			}
			else
			{
				IncreaseStack(Slot, SlotEmptySize);
				InterItem->SetAmount(InterItem->GetAmount() - SlotEmptySize);
			}
		}
	}
	int32 EmptySlotIndex = FindEmptySlot();
	if (Inventory.IsValidIndex(EmptySlotIndex))
	{
		Inventory[EmptySlotIndex].ID = InterItemID;
		Inventory[EmptySlotIndex].Amount = InterItem->GetAmount();
		InterItem->Destroy();
	}
	OnInventoryUpdated.Broadcast();
}

int32 UPawnInventoryComponent::FindEmptySlot() const
{
	int32 Index = 0;
	for (const auto& El : Inventory)
	{
		if (El.ID == EItemID::None)
		{
			return Index;
		}
		++Index;
	}
	return INDEX_NONE;
}

