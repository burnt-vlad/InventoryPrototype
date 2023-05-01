// InventoryPrototype / Fedosov Vladislav

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AmountSlider.generated.h"

class UBaseInventoryComponent;

UCLASS()
class INVENTORYPROTOTYPE_API UAmountSlider : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void InitializeAmountSlider(UBaseInventoryComponent* InventoryComp, const int32 InSourceIndex, const int32 DestinationIndex);

protected:
	virtual void NativeOnInitialized() override;
	UFUNCTION()
	void OnAmountSliderValueChanged(float NewValue);
	UFUNCTION()
	void OnAmountSliderCaptureEnd();

	UBaseInventoryComponent* InventoryComponent;
	int32 SourceIndex;
	int32 DestinationIndex;

	UPROPERTY(meta = (BindWidget))
	class UHorizontalBox* SliderHorizontalBox;
	UPROPERTY(meta = (BindWidget))
	class UBorder* SliderBorder;
	UPROPERTY(meta = (BindWidget))
	class UBorder* TextBorder;
	UPROPERTY(meta = (BindWidget))
	class USlider* AmountSlider;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* AmountTextBlock;
};
