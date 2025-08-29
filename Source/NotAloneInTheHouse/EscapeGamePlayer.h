#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "EscapeGamePlayer.generated.h"

/**
 * Player character for the escape game
 * First-person perspective with interaction capabilities
 */
UCLASS()
class NOTALONEINTHE_HOUSE_API AEscapeGamePlayer : public APawn
{
	GENERATED_BODY()

public:
	AEscapeGamePlayer();

protected:
	virtual void BeginPlay() override;

	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* FirstPersonCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* MeshComponent;

	// Movement properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MouseSensitivity;

	// Interaction properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	float InteractionRange;

	UPROPERTY(BlueprintReadOnly, Category = "Interaction")
	AActor* CurrentInteractable;

	// Fear system
	UPROPERTY(BlueprintReadWrite, Category = "Fear System")
	float FearLevel;

	UPROPERTY(BlueprintReadWrite, Category = "Fear System")
	float MaxFearLevel;

	// Inventory
	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	TArray<FString> Inventory;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	int32 MaxInventorySize;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Movement functions
	UFUNCTION()
	void MoveForward(float Value);

	UFUNCTION()
	void MoveRight(float Value);

	UFUNCTION()
	void Turn(float Value);

	UFUNCTION()
	void LookUp(float Value);

	// Interaction functions
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void Interact();

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void UpdateInteractable();

	UFUNCTION(BlueprintImplementableEvent, Category = "Interaction")
	void OnInteract(AActor* InteractedActor);

	// Fear system functions
	UFUNCTION(BlueprintCallable, Category = "Fear System")
	void IncreaseFear(float Amount);

	UFUNCTION(BlueprintCallable, Category = "Fear System")
	void DecreaseFear(float Amount);

	UFUNCTION(BlueprintImplementableEvent, Category = "Fear System")
	void OnFearLevelChanged(float NewFearLevel);

	// Inventory functions
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddItemToInventory(const FString& ItemName);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool RemoveItemFromInventory(const FString& ItemName);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool HasItem(const FString& ItemName);

	UFUNCTION(BlueprintImplementableEvent, Category = "Inventory")
	void OnInventoryChanged();
};