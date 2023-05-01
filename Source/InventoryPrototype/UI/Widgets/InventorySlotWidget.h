// InventoryPrototype / Fedosov Vladislav

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DataTypes.h"
#include "InventorySlotWidget.generated.h"

class USizeBox;
class UBorder;
class UBaseInventoryComponent;

UCLASS()
class INVENTORYPROTOTYPE_API UInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void InitializeInventorySlot(EItemID ID, int32 Amount, UBaseInventoryComponent* InventoryComponent);
	void SetIndex(int32 NewIndex) { Index = NewIndex; }
	int32 GetIndex() { return Index; }
	EItemID ItemSlotID;

protected:
	virtual FReply NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	void SetAmountTextBlock(int32 NewAmount);
	void SetSlotImage(UTexture2D* Texture);
	void DropItem();
	int32 Index;
	UBaseInventoryComponent* InventoryComp;

	UPROPERTY(meta = (BindWidget))
	USizeBox* SizeSlotBox;
	UPROPERTY(meta = (BindWidget))
	class UButton* SlotButton;
	UPROPERTY(meta = (BindWidget))
	UBorder* SlotBorder;
	UPROPERTY(meta = (BindWidget))
	class UOverlay* SlotOverlay;
	UPROPERTY(meta = (BindWidget))
	class UImage* SlotImage;
	UPROPERTY(meta = (BindWidget))
	USizeBox* AmountSizeBox;
	UPROPERTY(meta = (BindWidget))
	UBorder* AmountOuterBorder;
	UPROPERTY(meta = (BindWidget))
	UBorder* AmountInnerBorder;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* AmountTextBlock;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<class UUserWidget> AmountSliderWidgetClass;

};
