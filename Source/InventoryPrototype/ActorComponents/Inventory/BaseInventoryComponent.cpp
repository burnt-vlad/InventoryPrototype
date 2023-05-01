// InventoryPrototype / Fedosov Vladislav

#include "ActorComponents/Inventory/BaseInventoryComponent.h"
#include "Actors/Items/InteractableItemBase.h"

UBaseInventoryComponent::UBaseInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	ItemDataTableReference = TEXT("DataTable'/Game/Misc/DT_ItemProperties.DT_ItemProperties'");
	Inventory.SetNum(InventoryCapacity);
}

FItemProperties* UBaseInventoryComponent::GetItemProperties(EItemID ID) const
{
	const UDataTable* ItemTableObject = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *ItemDataTableReference));
	UEnum* MyEnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EItemID"), true);
	if (MyEnumPtr)
	{
		FString IDAsString = MyEnumPtr->GetEnumName((int32)ID);
		FItemProperties* ItemProperties = ItemTableObject->FindRow<FItemProperties>(FName(IDAsString), TEXT(""));
		return ItemProperties;
	}
	return nullptr;
}

int32 UBaseInventoryComponent::GetMaxStackSize(EItemID ID) const
{
	const FItemProperties* ItemProperties = GetItemProperties(ID);
	int32 StackSize = -1;
	if (ItemProperties)
	{
		StackSize = ItemProperties->StackSize;
	}
	checkf(StackSize > 0, TEXT("Stack size can only be greater than zero"))
	return StackSize;
}

void UBaseInventoryComponent::DropItem(int32 Index)
{
	if (!Inventory.IsValidIndex(Index)) return;
	FItemProperties* ItemProperties = GetItemProperties(Inventory[Index].ID);

	if (ItemProperties)
	{
		if (SpawnItemToDrop(Inventory[Index].Amount, ItemProperties))
		{
			MakeSlotNone(Index);
			OnInventoryUpdated.Broadcast();
		}
	}
}

bool UBaseInventoryComponent::SpawnItemToDrop(int32 AmountToDrop, FItemProperties* ItemProperties)
{
	UWorld* World = GetWorld();
	if (World)
	{
		FTransform SpawnTransform = FTransform(GetOwner()->GetActorRotation(), GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector() * 150.f);
		AInteractableItemBase* ItemToDrop = World->SpawnActorDeferred<AInteractableItemBase>(ItemProperties->ItemClass, SpawnTransform);
		if (ItemToDrop)
		{
			ItemToDrop->SetAmount(AmountToDrop);
			ItemToDrop->GetMesh()->SetSimulatePhysics(true);
			ItemToDrop->FinishSpawning(SpawnTransform);
			return true;
		}
	}
	return false;
}

 void UBaseInventoryComponent::TransferSlots(int32 SourceIndex, int32 DestinationIndex) 
{
	// The function is called when dragging an item from one slot to another slot (in inventory widget)

	if (!Inventory.IsValidIndex(SourceIndex) || !Inventory.IsValidIndex(DestinationIndex) || Inventory[SourceIndex].ID == EItemID::None) return;
	FItemData& SourceSlot = Inventory[SourceIndex];
	FItemData& DestinationSlot = Inventory[DestinationIndex];

	if (SourceSlot.ID != DestinationSlot.ID)
	{
		Inventory.Swap(SourceIndex, DestinationIndex);
	}
	else
	{
		const int32 DestinationSlotEmptySize = GetMaxStackSize(DestinationSlot.ID) - DestinationSlot.Amount;
		if (DestinationSlotEmptySize >= SourceSlot.Amount)
		{
			IncreaseStack(DestinationSlot, SourceSlot.Amount);
			MakeSlotNone(SourceIndex);
		}
		else
		{
			IncreaseStack(DestinationSlot, DestinationSlotEmptySize);
			DecreaseStack(SourceSlot, DestinationSlotEmptySize);
		}
	}
	OnInventoryUpdated.Broadcast();
 }

void UBaseInventoryComponent::SplitSlot(int32 SourceIndex, int32 DestinationIndex, int32 AmountToSplit)
{
	if (!Inventory.IsValidIndex(SourceIndex) || !Inventory.IsValidIndex(DestinationIndex) || Inventory[SourceIndex].ID == EItemID::None) return;

	FItemData& SourceSlot = Inventory[SourceIndex];
	FItemData& DestinationSlot = Inventory[DestinationIndex];

	if (DestinationSlot.ID == EItemID::None) 
	{
		// Split an slot into 2 slots with a given amount
		if (AmountToSplit == SourceSlot.Amount) 
		{
			// If the amount to split is equal to the source slot's amount, move the entire stack to the destination slot
			DestinationSlot.ID = SourceSlot.ID;
			IncreaseStack(DestinationSlot, AmountToSplit);
			MakeSlotNone(SourceIndex);
		}
		else if (AmountToSplit < SourceSlot.Amount) 
		{
			// If the amount to split is less than the source slot's amount, split the stack between the source and destination slots
			DestinationSlot.ID = SourceSlot.ID;
			DecreaseStack(SourceSlot, AmountToSplit);
			IncreaseStack(DestinationSlot, AmountToSplit);
		}
	}
	else if (SourceSlot.ID == DestinationSlot.ID) 
	{
		// Add some amount to the DestinationSlot depending on the empty space in the DestinationSlot
		const int32 DestinationSlotEmptySize = GetMaxStackSize(DestinationSlot.ID) - DestinationSlot.Amount;
		if (AmountToSplit == SourceSlot.Amount)
		{
			if (AmountToSplit <= DestinationSlotEmptySize)
			{
				IncreaseStack(DestinationSlot, AmountToSplit);
				MakeSlotNone(SourceIndex);
			}
			else
			{
				IncreaseStack(DestinationSlot, DestinationSlotEmptySize);
				DecreaseStack(SourceSlot, DestinationSlotEmptySize);
			}
		}
		else if (AmountToSplit < SourceSlot.Amount)
		{
			if (AmountToSplit <= DestinationSlotEmptySize)
			{
				IncreaseStack(DestinationSlot, AmountToSplit);
				DecreaseStack(SourceSlot, AmountToSplit);
			}
			else
			{
				DecreaseStack(SourceSlot, DestinationSlotEmptySize);
				IncreaseStack(DestinationSlot, DestinationSlotEmptySize);
			}
		}
	}
	OnInventoryUpdated.Broadcast();
}


void UBaseInventoryComponent::IncreaseStack(const int32 Index,const int32 Amount)
{
	if (Inventory.IsValidIndex(Index) && Inventory[Index].ID != EItemID::None)
	{
		const int32 MaxStackSize = GetMaxStackSize(Inventory[Index].ID);
		Inventory[Index].Amount = FMath::Clamp(Inventory[Index].Amount + Amount, 1, MaxStackSize);
	}
}

void UBaseInventoryComponent::IncreaseStack(FItemData& InventorySlot, const int32 Amount)
{
	const int32 MaxStackSize = GetMaxStackSize(InventorySlot.ID);
	InventorySlot.Amount = FMath::Clamp(InventorySlot.Amount + Amount, 1, MaxStackSize);
}

void UBaseInventoryComponent::DecreaseStack(const int32 Index,const int32 Amount)
{
	if (Inventory.IsValidIndex(Index) && Inventory[Index].ID != EItemID::None)
	{
		const int32 MaxStackSize = GetMaxStackSize(Inventory[Index].ID);
		Inventory[Index].Amount = FMath::Clamp(Inventory[Index].Amount - Amount, 1, MaxStackSize);
	}	
}

void UBaseInventoryComponent::DecreaseStack(FItemData& InventorySlot, const int32 Amount)
{
	const int32 MaxStackSize = GetMaxStackSize(InventorySlot.ID);
	InventorySlot.Amount = FMath::Clamp(InventorySlot.Amount - Amount, 1, MaxStackSize);
}

void UBaseInventoryComponent::MakeSlotNone(const int32 Index)
{
	if (Inventory.IsValidIndex(Index))
	{
		Inventory[Index].ID = EItemID::None;
		Inventory[Index].Amount = 0;
	}
}