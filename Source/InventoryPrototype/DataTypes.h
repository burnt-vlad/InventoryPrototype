#pragma once

#include "Engine/DataTable.h"
#include "DataTypes.generated.h"

class AInteractableItemBase;

UENUM(BlueprintType)
enum class EItemID : uint8
{
	None UMETA(DisplayName = "None"),
	Wood UMETA(DisplayName = "Wood"),
	Stone UMETA(DisplayName = "Stone"),
};

USTRUCT(BlueprintType)
struct FItemProperties : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties")
	EItemID ID;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties")
	FName ItemName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties")
	UTexture2D* Thumbnail;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties")
	int32 StackSize;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties")
	TSubclassOf<AInteractableItemBase> ItemClass;
};



USTRUCT(BlueprintType)
struct FItemData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Slot: Properties")
	EItemID ID = EItemID::None;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Slot: Properties")
	int32 Amount = 0;
};
