// InventoryPrototype / Fedosov Vladislav


#include "UI/Widgets/AmountSlider.h"
#include "Components/HorizontalBox.h"
#include "Components/Border.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "ActorComponents/Inventory/BaseInventoryComponent.h"

void UAmountSlider::NativeOnInitialized()
{
	AmountSlider->OnValueChanged.AddDynamic(this, &UAmountSlider::OnAmountSliderValueChanged);
	AmountSlider->OnMouseCaptureEnd.AddDynamic(this, &UAmountSlider::OnAmountSliderCaptureEnd);
	AmountSlider->MouseUsesStep = true;
	AmountSlider->StepSize = 1.f;
	AmountSlider->SetMinValue(1.f);
	AmountSlider->SetValue(1.f);
}

void UAmountSlider::InitializeAmountSlider(UBaseInventoryComponent* InventoryComp, const int32 InSourceIndex, const int32 InDestinationIndex)
{
	SourceIndex = InSourceIndex;
	DestinationIndex = InDestinationIndex;
	InventoryComponent = InventoryComp;
	if (InventoryComponent)
	{
		const auto& Inventory = InventoryComponent->GetInventory();
		AmountSlider->SetMaxValue((float)Inventory[InSourceIndex].Amount);
	}
}

void UAmountSlider::OnAmountSliderValueChanged(float NewValue)
{
	AmountTextBlock->SetText(FText::AsNumber(NewValue));
}

void UAmountSlider::OnAmountSliderCaptureEnd()
{
	const float SliderValue = AmountSlider->GetValue();
	if (InventoryComponent)
	{
		InventoryComponent->SplitSlot(SourceIndex, DestinationIndex, (int32)SliderValue);
		RemoveFromParent();
	}
}

