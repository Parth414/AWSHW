#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "HindWarfare_PS.generated.h"

UENUM()
enum EKillXP
{
	EVERYKILL,
	DOUBLEKILL,
	TRIPLEKILL,
	HEADSHOTKILL,
	LONGSHOTKILL,
	GRENADEKILL,
	VICTORY
};

UCLASS()
class HINDWARFARE_API AHindWarfare_PS : public APlayerState
{
	GENERATED_BODY()
private:
	int currentLevel = 0, maxLevels = 51, maxXP = 0, XPCount = 0;
	int everyKillXP = 10, doubleKillXP = 15, tripleKillXP = 20, headShotKillXP = 10,
		longShotKillXP = 10, grenadeKillXP = 10, victoryXP = 450;
	
	//delta time between current and previous kill. To calculate double and triple kill
	int killLatency = 3;


	TArray<int> maxLevelXPList =
	{
		0,500,1700,3500,6200,9500,13500,18200,23600,29700,
		36500,44300,53100,62900,73700,85500,98300,112100,
		126900,142700,159500,177300,196100,215900,236700,
		258500,281300,305100,329100,355700,382700,410900,
		440300,470900,502700,535700,569900,605300,641900,
		679700,718700,758900,800300,842900,886700,931700,
		977900,1025300,1073900,1123700,1175000
	};

public:
	virtual void ClientInitialize(class AController* C) override;

	UFUNCTION(BlueprintCallable)
	int GetLevelMaxXP(int levelNumber) const;
	
	UFUNCTION(BlueprintCallable)
	int GetNextLevel(int curLevel) const;
	
	UFUNCTION(BlueprintCallable)
	int GetKillXP(TEnumAsByte<EKillXP> killType) const;
	
	UFUNCTION(BlueprintCallable)
	bool IsDoubleKill(TArray<float> killTimeList) const;
	
	UFUNCTION(BlueprintCallable)
	bool IsTripleKill(TArray<float> killTimeList) const;
	
	UFUNCTION(BlueprintCallable)
	bool IsHeadKill(FName hitBoneName) const;
	
	UFUNCTION(BlueprintCallable)
	bool IsLongShotKill(FVector bulletImpactPoint, FVector gunNozlePos) const;
	
	UFUNCTION(BlueprintCallable)
	bool IsGrenadeKill() const;

	UFUNCTION(BlueprintCallable)
	bool IsVictoryXP() const;

	UFUNCTION(BlueprintCallable)
	void AddXP(int newXP);

	UFUNCTION(BlueprintCallable)
	void LevelUp();
};
