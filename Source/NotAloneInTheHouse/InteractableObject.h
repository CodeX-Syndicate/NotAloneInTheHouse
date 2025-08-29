#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "InteractableObject.generated.h"

UENUM(BlueprintType)
enum class EInteractableType : uint8
{
	Clue			UMETA(DisplayName = "Clue"),
	Key				UMETA(DisplayName = "Key"),
	Door			UMETA(DisplayName = "Door"),
	Puzzle			UMETA(DisplayName = "Puzzle"),
	Item			UMETA(DisplayName = "Item"),
	Journal			UMETA(DisplayName = "Journal"),
	Furniture		UMETA(DisplayName = "Furniture"),
	SupernaturalObject	UMETA(DisplayName = "Supernatural Object")
};

/**
 * Base class for all interactable objects in the haunted house
 */
UCLASS()
class NOTALONEINTHE_HOUSE_API AInteractableObject : public AActor
{
	GENERATED_BODY()
	
public:	
	AInteractableObject();

protected:
	virtual void BeginPlay() override;

	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* InteractionBox;

	// Interactable properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	EInteractableType InteractableType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	FString ObjectName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	FString InteractionText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	bool bCanInteract;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	bool bIsOneTimeUse;

	UPROPERTY(BlueprintReadOnly, Category = "Interaction")
	bool bHasBeenUsed;

	// Clue/Key properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Logic", meta = (EditCondition = "InteractableType == EInteractableType::Clue"))
	FString ClueText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Logic", meta = (EditCondition = "InteractableType == EInteractableType::Key"))
	FString KeyID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Logic", meta = (EditCondition = "InteractableType == EInteractableType::Door"))
	FString RequiredKeyID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Logic", meta = (EditCondition = "InteractableType == EInteractableType::Door"))
	bool bIsLocked;

	// Supernatural properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Supernatural")
	bool bTriggersSupernatural;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Supernatural")
	FString SupernaturalEventName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Supernatural")
	float FearAmount;

public:	
	virtual void Tick(float DeltaTime) override;

	// Interaction functions
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	virtual void OnInteracted(AActor* InteractingActor);

	UFUNCTION(BlueprintImplementableEvent, Category = "Interaction")
	void OnInteractionStart(AActor* InteractingActor);

	UFUNCTION(BlueprintImplementableEvent, Category = "Interaction")
	void OnInteractionEnd(AActor* InteractingActor);

	// Specific interaction types
	UFUNCTION(BlueprintCallable, Category = "Game Logic")
	void CollectClue(AActor* Player);

	UFUNCTION(BlueprintCallable, Category = "Game Logic")
	void CollectKey(AActor* Player);

	UFUNCTION(BlueprintCallable, Category = "Game Logic")
	void OpenDoor(AActor* Player);

	UFUNCTION(BlueprintCallable, Category = "Game Logic")
	void TriggerPuzzle(AActor* Player);

	// Supernatural functions
	UFUNCTION(BlueprintCallable, Category = "Supernatural")
	void TriggerSupernaturalEvent(AActor* Player);

	// Getters
	UFUNCTION(BlueprintPure, Category = "Interaction")
	EInteractableType GetInteractableType() const { return InteractableType; }

	UFUNCTION(BlueprintPure, Category = "Interaction")
	FString GetObjectName() const { return ObjectName; }

	UFUNCTION(BlueprintPure, Category = "Interaction")
	FString GetInteractionText() const { return InteractionText; }

	UFUNCTION(BlueprintPure, Category = "Interaction")
	bool GetCanInteract() const { return bCanInteract && (!bIsOneTimeUse || !bHasBeenUsed); }
};