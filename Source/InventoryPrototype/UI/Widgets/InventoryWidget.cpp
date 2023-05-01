// InventoryPrototype / Fedosov Vladislav


#include "UI/Widgets/InventoryWidget.h"
#include "ActorComponents/Inventory/BaseInventoryComponent.h"
#include "Components/WrapBox.h"
#include "UI/Widgets/InventorySlotWidget.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	bIsFocusable = 1;
}

void UInventoryWidget::InitializeInventoryWidget(UBaseInventoryComponent* InventoryComp)
{
	InventoryComponent = InventoryComp;
	if (InventoryComponent)
	{
		InventoryComponent->OnInventoryUpdated.AddUObject(this, &UInventoryWidget::UpdateWrapBox);
		UpdateWrapBox();
	}
}

void UInventoryWidget::UpdateWrapBox()
{
	WrapBoxA->ClearChildren();
	if (InventoryComponent && InventorySlotClass)
	{
		const TArray<FItemData> Slots = InventoryComponent->GetInventory();
		for (int32 i = 0; i < Slots.Num(); i++)
		{
			auto SlotWidget = CreateWidget<UInventorySlotWidget>(GetWorld(), InventorySlotClass);
			if (SlotWidget)
			{
				SlotWidget->InitializeInventorySlot(Slots[i].ID, Slots[i].Amount, InventoryComponent);
				SlotWidget->SetIndex(i);
				WrapBoxA->AddChild(SlotWidget);
			}
		}
	}
}

