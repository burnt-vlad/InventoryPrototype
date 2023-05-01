// InventoryPrototype / Fedosov Vladislav

#include "Characters/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "ActorComponents/Inventory/PawnInventoryComponent.h"
#include "Actors/Items/InteractableItemBase.h"
#include "DrawDebugHelpers.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(GetRootComponent());
	InventoryComponent = CreateDefaultSubobject<UPawnInventoryComponent>("InventoryComponent");
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerCharacter::MoveForward(float Amount)
{
	AddMovementInput(GetActorForwardVector(), Amount);
}

void APlayerCharacter::MoveRight(float Amount)
{
	AddMovementInput(GetActorRightVector(), Amount);
}

void APlayerCharacter::TurnUp(float Amount)
{
	AddControllerPitchInput(Amount);
}

void APlayerCharacter::TurnRight(float Amount)
{
	AddControllerYawInput(Amount);
}

void APlayerCharacter::PickUpItem()
{
	AInteractableItemBase* Item = TraceForItems();
	if (Item)
	{
		if (InventoryComponent)
		{
			InventoryComponent->AddToInventory(Item);
		}
	}
}

AInteractableItemBase* APlayerCharacter::TraceForItems()
{
	FVector TraceStart, TraceEnd;
	if (GetPickupTraceStartEndLocation(TraceStart, TraceEnd))
	{
		FHitResult CameraTraceHitResult;
		GetWorld()->LineTraceSingleByChannel(CameraTraceHitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility);
		DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 40.f, 0, 3.f);
		if (CameraTraceHitResult.bBlockingHit)
		{
			const auto ItemTraceHit = Cast<AInteractableItemBase>(CameraTraceHitResult.Actor);
			if (ItemTraceHit)
				return ItemTraceHit;
		}
	}
	return nullptr;
}

bool APlayerCharacter::GetPickupTraceStartEndLocation(FVector& TraceStart, FVector& TraceEnd)
{
	if (Camera)
	{
		FTransform CameraTransform = Camera->GetComponentTransform();
		TraceStart = CameraTransform.GetLocation();
		FVector TraceDirection = CameraTransform.GetRotation().Vector();
		TraceEnd = TraceStart + TraceDirection * PickupTraceLength;
		return true;
	}
	return false;
}