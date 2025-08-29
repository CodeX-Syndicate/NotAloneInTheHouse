#include "InteractableObject.h"
#include "EscapeGamePlayer.h"
#include "NotAloneInTheHouseGameModeBase.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"

AInteractableObject::AInteractableObject()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create components
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;

	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
	InteractionBox->SetupAttachment(MeshComponent);
	InteractionBox->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));

	// Add Interactable tag
	Tags.Add(TEXT("Interactable"));

	// Initialize properties
	InteractableType = EInteractableType::Item;
	ObjectName = TEXT("Mysterious Object");
	InteractionText = TEXT("Examine");
	bCanInteract = true;
	bIsOneTimeUse = false;
	bHasBeenUsed = false;
	ClueText = TEXT("");
	KeyID = TEXT("");
	RequiredKeyID = TEXT("");
	bIsLocked = false;
	bTriggersSupernatural = false;
	SupernaturalEventName = TEXT("");
	FearAmount = 0.0f;
}

void AInteractableObject::BeginPlay()
{
	Super::BeginPlay();
}

void AInteractableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInteractableObject::OnInteracted(AActor* InteractingActor)
{
	if (!GetCanInteract())
	{
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("InteractableObject: %s was interacted with by %s"), *ObjectName, *InteractingActor->GetName());

	// Trigger interaction start event
	OnInteractionStart(InteractingActor);

	// Handle different interaction types
	switch (InteractableType)
	{
		case EInteractableType::Clue:
			CollectClue(InteractingActor);
			break;
			
		case EInteractableType::Key:
			CollectKey(InteractingActor);
			break;
			
		case EInteractableType::Door:
			OpenDoor(InteractingActor);
			break;
			
		case EInteractableType::Puzzle:
			TriggerPuzzle(InteractingActor);
			break;
			
		case EInteractableType::SupernaturalObject:
			TriggerSupernaturalEvent(InteractingActor);
			break;
			
		default:
			// Generic item interaction
			UE_LOG(LogTemp, Warning, TEXT("InteractableObject: Generic interaction with %s"), *ObjectName);
			break;
	}

	// Mark as used if one-time use
	if (bIsOneTimeUse)
	{
		bHasBeenUsed = true;
	}

	// Trigger supernatural events if configured
	if (bTriggersSupernatural && !SupernaturalEventName.IsEmpty())
	{
		TriggerSupernaturalEvent(InteractingActor);
	}

	// Trigger interaction end event
	OnInteractionEnd(InteractingActor);
}

void AInteractableObject::CollectClue(AActor* Player)
{
	UE_LOG(LogTemp, Warning, TEXT("InteractableObject: Clue collected - %s"), *ClueText);

	// Add clue to player's inventory
	if (AEscapeGamePlayer* EscapePlayer = Cast<AEscapeGamePlayer>(Player))
	{
		EscapePlayer->AddItemToInventory(ObjectName);
	}

	// Notify game mode about clue found
	if (ANotAloneInTheHouseGameModeBase* GameMode = Cast<ANotAloneInTheHouseGameModeBase>(UGameplayStatics::GetGameMode(this)))
	{
		GameMode->FindClue();
	}

	// Hide the clue object
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
}

void AInteractableObject::CollectKey(AActor* Player)
{
	UE_LOG(LogTemp, Warning, TEXT("InteractableObject: Key collected - %s"), *KeyID);

	// Add key to player's inventory
	if (AEscapeGamePlayer* EscapePlayer = Cast<AEscapeGamePlayer>(Player))
	{
		EscapePlayer->AddItemToInventory(KeyID);
	}

	// Hide the key object
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
}

void AInteractableObject::OpenDoor(AActor* Player)
{
	if (bIsLocked)
	{
		// Check if player has the required key
		if (AEscapeGamePlayer* EscapePlayer = Cast<AEscapeGamePlayer>(Player))
		{
			if (EscapePlayer->HasItem(RequiredKeyID))
			{
				UE_LOG(LogTemp, Warning, TEXT("InteractableObject: Door unlocked with key %s"), *RequiredKeyID);
				bIsLocked = false;
				
				// Use the key
				EscapePlayer->RemoveItemFromInventory(RequiredKeyID);
				
				// Open the door (this would typically involve animation or level transition)
				UE_LOG(LogTemp, Warning, TEXT("InteractableObject: Door %s is now open!"), *ObjectName);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("InteractableObject: Door is locked. Need key: %s"), *RequiredKeyID);
				
				// Increase fear slightly for trying locked doors
				EscapePlayer->IncreaseFear(5.0f);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("InteractableObject: Door %s is already unlocked"), *ObjectName);
	}
}

void AInteractableObject::TriggerPuzzle(AActor* Player)
{
	UE_LOG(LogTemp, Warning, TEXT("InteractableObject: Puzzle triggered - %s"), *ObjectName);
	
	// This would typically open a puzzle UI or start a puzzle sequence
	// For now, we'll just log it and potentially reward the player
}

void AInteractableObject::TriggerSupernaturalEvent(AActor* Player)
{
	UE_LOG(LogTemp, Warning, TEXT("InteractableObject: Supernatural event triggered - %s"), *SupernaturalEventName);

	// Increase player's fear
	if (AEscapeGamePlayer* EscapePlayer = Cast<AEscapeGamePlayer>(Player))
	{
		EscapePlayer->IncreaseFear(FearAmount);
	}

	// Trigger supernatural event in game mode
	if (ANotAloneInTheHouseGameModeBase* GameMode = Cast<ANotAloneInTheHouseGameModeBase>(UGameplayStatics::GetGameMode(this)))
	{
		GameMode->TriggerSupernaturalEvent(SupernaturalEventName);
	}
}