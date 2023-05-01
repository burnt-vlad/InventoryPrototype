// InventoryPrototype / Fedosov Vladislav

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameFramework/PlayerController.h"
#include "PlayerHUD.generated.h"

UCLASS()
class INVENTORYPROTOTYPE_API APlayerHUD : public AHUD
{
	GENERATED_BODY()

public:
	void ShowInventory(APlayerController* Controller);
	void HideInventory();
	bool IsInventoryActive() { return bIsInventoryActive; }

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> InventoryWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	class UInventoryWidget* InventoryWidget;

private:
	bool bIsInventoryActive = false;
};
