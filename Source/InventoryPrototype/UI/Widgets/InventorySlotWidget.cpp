// InventoryPrototype / Fedosov Vladislav

#include "UI/Widgets/InventorySlotWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/CanvasPanel.h"
#include "Components/SizeBox.h"
#include "Components/Border.h"
#include "Components/Overlay.h"
#include "Components/TextBlock.h"
#include "ActorComponents/Inventory/BaseInventoryComponent.h"
#include "UI/DragDropOperations/SlotDragDrop.h"
#include "UI/Widgets/AmountSlider.h"

void UInventorySlotWidget::InitializeInventorySlot(EItemID ID, int32 Amount, UBaseInventoryComponent* InventoryComponent)
{
	InventoryComp = InventoryComponent;
	if (InventoryComp)
	{
		ItemSlotID = ID;
		if (ItemSlotID == EItemID::None)
		{
			SlotImage->SetColorAndOpacity(FLinearColor(FColor::Black));
			AmountOuterBorder->SetVisibility(ESlateVisibility::Hidden);
			return;
		}
		else
		{
			auto ItemProperties = InventoryComp->GetItemProperties(ItemSlotID);
			if (ItemProperties)
			{
				SetSlotImage(ItemProperties->Thumbnail);
				SetAmountTextBlock(Amount);
			}
		}
	}
}

FReply UInventorySlotWidget::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton && ItemSlotID != EItemID::None)
	{
		Reply.DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
		return Reply;
	}
	if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton && ItemSlotID != EItemID::None)
	{
		DropItem();
	}
	return Reply;
}

void UInventorySlotWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{ 

	USlotDragDrop* SlotDragDrop = NewObject<USlotDragDrop>();
	if (SlotDragDrop)
	{
		SlotDragDrop->SetIndex(Index);
		SlotDragDrop->DefaultDragVisual = this;
		OutOperation = SlotDragDrop;
	}

}

bool UInventorySlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	const auto DDOperation = Cast<USlotDragDrop>(InOperation);
	if (DDOperation)
	{
		if (DDOperation->GetIndex() != Index)
		{
			if(InDragDropEvent.GetModifierKeys().IsShiftDown()) //If the shift is pressed, the slider widget will be created
			{
				if (AmountSliderWidgetClass)
				{
					const auto AmountWidget = CreateWidget<UAmountSlider>(GetWorld(), AmountSliderWidgetClass);
					if (AmountWidget)
					{
						FVector2D CursorPosition = InDragDropEvent.GetScreenSpacePosition();
						FVector2D WidgetPosition = InGeometry.AbsoluteToLocal(CursorPosition);
						AmountWidget->SetPositionInViewport(CursorPosition);
						AmountWidget->InitializeAmountSlider(InventoryComp, DDOperation->GetIndex(), Index);
						AmountWidget->AddToViewport();
					}
				}
			}
			else 
			{
				if (InventoryComp)
				{
					InventoryComp->TransferSlots(DDOperation->GetIndex(), Index);
				}
			}
			return true;
		}
	}
	return false;
}

void UInventorySlotWidget::DropItem()
{
	if (InventoryComp)
	{
		InventoryComp->DropItem(Index);
	}
}

void UInventorySlotWidget::SetSlotImage(UTexture2D* Texture)
{
	if (SlotImage && Texture)
	{
		SlotImage->SetBrushFromTexture(Texture);
	}
}

void UInventorySlotWidget::SetAmountTextBlock(int32 NewAmount)
{
	if (AmountTextBlock)
	{
		AmountTextBlock->SetText(FText::AsNumber(NewAmount));
	}
}
