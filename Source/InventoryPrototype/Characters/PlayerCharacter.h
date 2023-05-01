// InventoryPrototype / Fedosov Vladislav

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UPawnInventoryComponent;

UCLASS()
class INVENTORYPROTOTYPE_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void PickUpItem();
	void MoveForward(float Amount);
	void MoveRight(float Amount);
	void TurnUp(float Amount);
	void TurnRight(float Amount);

protected:
	class AInteractableItemBase* TraceForItems();
	bool GetPickupTraceStartEndLocation(FVector& TraceStart, FVector& TraceEnd);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UCameraComponent* Camera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UPawnInventoryComponent* InventoryComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera: Inventory")
	float PickupTraceLength = 450.f;
};
