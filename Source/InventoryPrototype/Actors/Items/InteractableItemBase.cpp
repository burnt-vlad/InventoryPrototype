// InventoryPrototype / Fedosov Vladislav

#include "Actors/Items/InteractableItemBase.h"

AInteractableItemBase::AInteractableItemBase()
{
	PrimaryActorTick.bCanEverTick = false;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	SetRootComponent(StaticMesh);
}

