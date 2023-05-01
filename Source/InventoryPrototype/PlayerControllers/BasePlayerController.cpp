// InventoryPrototype / Fedosov Vladislav

#include "PlayerControllers/BasePlayerController.h"
#include "Characters/PlayerCharacter.h"
#include "UI/HUDs/PlayerHUD.h"

void ABasePlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	ControlledPlayerCharacter = Cast<APlayerCharacter>(InPawn);
	PlayerHUD = Cast<APlayerHUD>(GetHUD());
}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &ABasePlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ABasePlayerController::MoveRight);
	InputComponent->BindAxis("TurnUp", this, &ABasePlayerController::TurnUp);
	InputComponent->BindAxis("TurnRight", this, &ABasePlayerController::TurnRight);
	InputComponent->BindAction("PickUp", IE_Pressed, this, &ABasePlayerController::PickUpItem);
	InputComponent->BindAction("ShowInventory", IE_Pressed, this, &ABasePlayerController::ShowInventory);
}

void ABasePlayerController::MoveForward(float Amount)
{
	if (ControlledPlayerCharacter.IsValid())
	{
		ControlledPlayerCharacter->MoveForward(Amount);
	}
}

void ABasePlayerController::MoveRight(float Amount)
{
	if (ControlledPlayerCharacter.IsValid())
	{
		ControlledPlayerCharacter->MoveRight(Amount);
	}
}

void ABasePlayerController::TurnUp(float Amount)
{
	if (ControlledPlayerCharacter.IsValid())
	{
		ControlledPlayerCharacter->TurnUp(Amount);
	}
}

void ABasePlayerController::TurnRight(float Amount)
{
	if (ControlledPlayerCharacter.IsValid())
	{
		ControlledPlayerCharacter->TurnRight(Amount);
	}
}

void ABasePlayerController::PickUpItem()
{
	if (ControlledPlayerCharacter.IsValid())
	{
		ControlledPlayerCharacter->PickUpItem();
	}
}

void ABasePlayerController::ShowInventory()
{
	if (PlayerHUD)
	{
		if (PlayerHUD->IsInventoryActive())
		{
			PlayerHUD->HideInventory();
			SetInputMode(FInputModeGameOnly());
			bShowMouseCursor = false;
		}
		else
		{
			PlayerHUD->ShowInventory(this);
			SetInputMode(FInputModeGameAndUI());
			bShowMouseCursor = true;
		}
	}
}
