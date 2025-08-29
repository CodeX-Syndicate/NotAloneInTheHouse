#include "NotAloneInTheHouseGameModeBase.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"

ANotAloneInTheHouseGameModeBase::ANotAloneInTheHouseGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;

	// Initialize game state
	bGameStarted = false;
	bGameWon = false;
	CluesFound = 0;
	TotalClues = 10; // Default number of clues needed to escape
	ParanormalActivityLevel = 0.0f;

	// Initialize supernatural events
	SupernaturalEvents.Add(TEXT("Door Slam"));
	SupernaturalEvents.Add(TEXT("Lights Flicker"));
	SupernaturalEvents.Add(TEXT("Whispers"));
	SupernaturalEvents.Add(TEXT("Cold Spot"));
	SupernaturalEvents.Add(TEXT("Shadow Movement"));
	SupernaturalEvents.Add(TEXT("Object Movement"));
	SupernaturalEvents.Add(TEXT("Footsteps"));
	SupernaturalEvents.Add(TEXT("Mysterious Sound"));
}

void ANotAloneInTheHouseGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	// Automatically start the game after a brief delay
	FTimerHandle StartGameTimer;
	GetWorldTimerManager().SetTimer(StartGameTimer, this, &ANotAloneInTheHouseGameModeBase::StartGame, 3.0f, false);
}

void ANotAloneInTheHouseGameModeBase::StartGame()
{
	if (!bGameStarted)
	{
		bGameStarted = true;
		
		// Log game start
		UE_LOG(LogTemp, Warning, TEXT("NotAloneInTheHouse: Game Started! Find %d clues to escape the haunted house."), TotalClues);
		
		// Trigger Blueprint event
		OnGameStart();
		
		// Start with low paranormal activity
		ParanormalActivityLevel = 10.0f;
	}
}

void ANotAloneInTheHouseGameModeBase::FindClue()
{
	if (bGameStarted && !bGameWon)
	{
		CluesFound++;
		
		// Log clue found
		UE_LOG(LogTemp, Warning, TEXT("NotAloneInTheHouse: Clue found! (%d/%d)"), CluesFound, TotalClues);
		
		// Increase paranormal activity with each clue found
		IncreaseParanormalActivity(5.0f);
		
		// Trigger random supernatural event
		if (SupernaturalEvents.Num() > 0)
		{
			int32 RandomIndex = FMath::RandRange(0, SupernaturalEvents.Num() - 1);
			TriggerSupernaturalEvent(SupernaturalEvents[RandomIndex]);
		}
		
		// Trigger Blueprint event
		OnClueFound(TotalClues - CluesFound);
		
		// Check if player has won
		CheckVictoryCondition();
	}
}

void ANotAloneInTheHouseGameModeBase::CheckVictoryCondition()
{
	if (CluesFound >= TotalClues && !bGameWon)
	{
		TriggerVictory();
	}
}

void ANotAloneInTheHouseGameModeBase::TriggerVictory()
{
	if (!bGameWon)
	{
		bGameWon = true;
		
		// Log victory
		UE_LOG(LogTemp, Warning, TEXT("NotAloneInTheHouse: Congratulations! You've escaped the haunted house!"));
		
		// Trigger Blueprint event
		OnVictory();
	}
}

void ANotAloneInTheHouseGameModeBase::IncreaseParanormalActivity(float Amount)
{
	ParanormalActivityLevel = FMath::Clamp(ParanormalActivityLevel + Amount, 0.0f, 100.0f);
	
	UE_LOG(LogTemp, Log, TEXT("NotAloneInTheHouse: Paranormal activity increased to %f"), ParanormalActivityLevel);
}

void ANotAloneInTheHouseGameModeBase::TriggerSupernaturalEvent(const FString& EventName)
{
	UE_LOG(LogTemp, Warning, TEXT("NotAloneInTheHouse: Supernatural Event - %s"), *EventName);
	
	// Trigger Blueprint event
	OnSupernaturalEvent(EventName);
}