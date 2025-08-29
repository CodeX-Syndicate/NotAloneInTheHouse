#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NotAloneInTheHouseGameModeBase.generated.h"

/**
 * Game mode for the haunted house escape game
 * Manages game state, victory conditions, and supernatural events
 */
UCLASS()
class NOTALONEINTHE_HOUSE_API ANotAloneInTheHouseGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ANotAloneInTheHouseGameModeBase();

protected:
	virtual void BeginPlay() override;

	// Game state management
	UPROPERTY(BlueprintReadWrite, Category = "Game State")
	bool bGameStarted;

	UPROPERTY(BlueprintReadWrite, Category = "Game State")
	bool bGameWon;

	UPROPERTY(BlueprintReadWrite, Category = "Game State")
	int32 CluesFound;

	UPROPERTY(BlueprintReadWrite, Category = "Game State")
	int32 TotalClues;

	// Supernatural events
	UPROPERTY(BlueprintReadWrite, Category = "Supernatural")
	float ParanormalActivityLevel;

	UPROPERTY(BlueprintReadWrite, Category = "Supernatural")
	TArray<FString> SupernaturalEvents;

public:
	// Game progression functions
	UFUNCTION(BlueprintCallable, Category = "Game Progression")
	void StartGame();

	UFUNCTION(BlueprintCallable, Category = "Game Progression")
	void FindClue();

	UFUNCTION(BlueprintCallable, Category = "Game Progression")
	void CheckVictoryCondition();

	UFUNCTION(BlueprintCallable, Category = "Game Progression")
	void TriggerVictory();

	// Supernatural event functions
	UFUNCTION(BlueprintCallable, Category = "Supernatural")
	void IncreaseParanormalActivity(float Amount);

	UFUNCTION(BlueprintCallable, Category = "Supernatural")
	void TriggerSupernaturalEvent(const FString& EventName);

	UFUNCTION(BlueprintImplementableEvent, Category = "Supernatural")
	void OnSupernaturalEvent(const FString& EventName);

	UFUNCTION(BlueprintImplementableEvent, Category = "Game Events")
	void OnGameStart();

	UFUNCTION(BlueprintImplementableEvent, Category = "Game Events")
	void OnClueFound(int32 CluesRemaining);

	UFUNCTION(BlueprintImplementableEvent, Category = "Game Events")
	void OnVictory();
};