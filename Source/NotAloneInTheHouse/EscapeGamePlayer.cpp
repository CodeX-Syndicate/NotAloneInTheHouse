#include "EscapeGamePlayer.h"
#include "Engine/Engine.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

AEscapeGamePlayer::AEscapeGamePlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create components
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	RootComponent = CapsuleComponent;
	CapsuleComponent->SetCapsuleHalfHeight(96.0f);
	CapsuleComponent->SetCapsuleRadius(34.0f);

	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(CapsuleComponent);
	FirstPersonCamera->SetRelativeLocation(FVector(0.0f, 0.0f, 64.0f));
	FirstPersonCamera->bUsePawnControlRotation = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(CapsuleComponent);

	// Initialize properties
	MovementSpeed = 300.0f;
	MouseSensitivity = 1.0f;
	InteractionRange = 200.0f;
	CurrentInteractable = nullptr;
	FearLevel = 0.0f;
	MaxFearLevel = 100.0f;
	MaxInventorySize = 10;
}

void AEscapeGamePlayer::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Warning, TEXT("EscapeGamePlayer: Player spawned in the haunted house."));
}

void AEscapeGamePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Update interactable detection
	UpdateInteractable();

	// Gradually decrease fear over time (if not being scared)
	if (FearLevel > 0.0f)
	{
		DecreaseFear(5.0f * DeltaTime);
	}
}

void AEscapeGamePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Movement bindings
	PlayerInputComponent->BindAxis("MoveForward", this, &AEscapeGamePlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AEscapeGamePlayer::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AEscapeGamePlayer::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AEscapeGamePlayer::LookUp);

	// Interaction bindings
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AEscapeGamePlayer::Interact);
}

void AEscapeGamePlayer::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		const FVector Direction = FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value * MovementSpeed);
	}
}

void AEscapeGamePlayer::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		const FVector Direction = FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value * MovementSpeed);
	}
}

void AEscapeGamePlayer::Turn(float Value)
{
	AddControllerYawInput(Value * MouseSensitivity);
}

void AEscapeGamePlayer::LookUp(float Value)
{
	AddControllerPitchInput(Value * MouseSensitivity);
}

void AEscapeGamePlayer::Interact()
{
	if (CurrentInteractable)
	{
		UE_LOG(LogTemp, Warning, TEXT("EscapeGamePlayer: Interacting with %s"), *CurrentInteractable->GetName());
		OnInteract(CurrentInteractable);
	}
}

void AEscapeGamePlayer::UpdateInteractable()
{
	// Perform line trace to find interactable objects
	FVector Start = FirstPersonCamera->GetComponentLocation();
	FVector Forward = FirstPersonCamera->GetForwardVector();
	FVector End = Start + (Forward * InteractionRange);

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		Start,
		End,
		ECC_Visibility,
		QueryParams
	);

	AActor* NewInteractable = nullptr;
	if (bHit && HitResult.GetActor())
	{
		// Check if the hit actor has an "Interactable" tag
		if (HitResult.GetActor()->ActorHasTag(TEXT("Interactable")))
		{
			NewInteractable = HitResult.GetActor();
		}
	}

	// Update current interactable
	if (CurrentInteractable != NewInteractable)
	{
		CurrentInteractable = NewInteractable;
		
		if (CurrentInteractable)
		{
			UE_LOG(LogTemp, Log, TEXT("EscapeGamePlayer: Can interact with %s"), *CurrentInteractable->GetName());
		}
	}
}

void AEscapeGamePlayer::IncreaseFear(float Amount)
{
	FearLevel = FMath::Clamp(FearLevel + Amount, 0.0f, MaxFearLevel);
	OnFearLevelChanged(FearLevel);
	
	UE_LOG(LogTemp, Warning, TEXT("EscapeGamePlayer: Fear increased! Current level: %f"), FearLevel);
}

void AEscapeGamePlayer::DecreaseFear(float Amount)
{
	FearLevel = FMath::Clamp(FearLevel - Amount, 0.0f, MaxFearLevel);
	OnFearLevelChanged(FearLevel);
}

bool AEscapeGamePlayer::AddItemToInventory(const FString& ItemName)
{
	if (Inventory.Num() < MaxInventorySize)
	{
		Inventory.Add(ItemName);
		OnInventoryChanged();
		
		UE_LOG(LogTemp, Warning, TEXT("EscapeGamePlayer: Added %s to inventory"), *ItemName);
		return true;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("EscapeGamePlayer: Inventory full! Cannot add %s"), *ItemName);
	return false;
}

bool AEscapeGamePlayer::RemoveItemFromInventory(const FString& ItemName)
{
	int32 ItemIndex = Inventory.Find(ItemName);
	if (ItemIndex != INDEX_NONE)
	{
		Inventory.RemoveAt(ItemIndex);
		OnInventoryChanged();
		
		UE_LOG(LogTemp, Warning, TEXT("EscapeGamePlayer: Removed %s from inventory"), *ItemName);
		return true;
	}
	
	return false;
}

bool AEscapeGamePlayer::HasItem(const FString& ItemName)
{
	return Inventory.Contains(ItemName);
}