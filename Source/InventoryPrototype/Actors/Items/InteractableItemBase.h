// InventoryPrototype / Fedosov Vladislav

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DataTypes.h"
#include "InteractableItemBase.generated.h"

UCLASS(Abstract, Blueprintable)
class INVENTORYPROTOTYPE_API AInteractableItemBase : public AActor
{
	GENERATED_BODY()

public:
	AInteractableItemBase();
	EItemID GetID() const { return ItemData.ID; }
	int32 GetAmount() const { return ItemData.Amount; }
	void SetAmount(int32 NewAmount) { ItemData.Amount = NewAmount; }
	UStaticMeshComponent* GetMesh() const { return StaticMesh; }

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item: Properties")
	FItemData ItemData;
};
