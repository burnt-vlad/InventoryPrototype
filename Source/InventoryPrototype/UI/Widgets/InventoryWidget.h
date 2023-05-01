// InventoryPrototype / Fedosov Vladislav

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

class UBaseInventoryComponent;

UCLASS()
class INVENTORYPROTOTYPE_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	void InitializeInventoryWidget(UBaseInventoryComponent* InventoryComp);

	protected:
	void UpdateWrapBox();

	UBaseInventoryComponent* InventoryComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> InventorySlotClass;
	UPROPERTY(meta = (BindWidget))
	class UWrapBox* WrapBoxA;
};
