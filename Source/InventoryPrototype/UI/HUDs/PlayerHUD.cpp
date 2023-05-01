// InventoryPrototype / Fedosov Vladislav

#include "UI/HUDs/PlayerHUD.h"
#include "UI/Widgets/InventoryWidget.h"
#include "Characters/PlayerCharacter.h"
#include "ActorComponents/Inventory/BaseInventoryComponent.h"

void APlayerHUD::ShowInventory(APlayerController* Controller)
{
	if (InventoryWidgetClass)
	{
		InventoryWidget = CreateWidget<UInventoryWidget>(GetWorld(), InventoryWidgetClass);
		if (InventoryWidget)
		{
			const auto PlayerCharater = Cast<APlayerCharacter>(GetOwningPawn());
			if (PlayerCharater)
			{
				const auto InventoryComponent = PlayerCharater->FindComponentByClass<UBaseInventoryComponent>();
				if (InventoryComponent)
				{
					InventoryWidget->InitializeInventoryWidget(InventoryComponent);
					InventoryWidget->AddToViewport();
					bIsInventoryActive = true;
				}
			}
		}
	}
}

void APlayerHUD::HideInventory()
{
	if (InventoryWidget)
	{
		InventoryWidget->RemoveFromViewport();
		bIsInventoryActive = false;
	}
}

