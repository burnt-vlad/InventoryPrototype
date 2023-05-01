// InventoryPrototype / Fedosov Vladislav

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

UCLASS()
class INVENTORYPROTOTYPE_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void SetPawn(APawn* InPawn) override;

protected:
	virtual void SetupInputComponent() override;

private:
	void MoveForward(float Amount);
	void MoveRight(float Amount);
	void TurnUp(float Amount);
	void TurnRight(float Amount);
	void PickUpItem();
	void ShowInventory();
	void HideInventory();

	TSoftObjectPtr <class APlayerHUD> PlayerHUD;
	TSoftObjectPtr<class APlayerCharacter> ControlledPlayerCharacter;
};
