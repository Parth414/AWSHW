#include "HindWarfare_PS.h"

void AHindWarfare_PS::ClientInitialize(AController* C)
{
	//initialize currentLevel and XPCount;
	UE_LOG(LogTemp,Warning,TEXT("oooo Initialized  player state"));
}

int AHindWarfare_PS::GetLevelMaxXP(int levelNumber) const
{
	return maxLevelXPList[levelNumber + 1];
}

int AHindWarfare_PS::GetNextLevel(int curLevel) const
{
	return (curLevel + 1) >= maxLevels ? maxLevels : curLevel + 1;
}

int AHindWarfare_PS::GetKillXP(TEnumAsByte<EKillXP> killType) const
{
	switch (killType)
	{
		case EKillXP::EVERYKILL:
			return everyKillXP;
			break;

		case EKillXP::DOUBLEKILL:
			return doubleKillXP;
			break;

		case EKillXP::TRIPLEKILL:
			return tripleKillXP;
			break;

		case EKillXP::HEADSHOTKILL:
			return headShotKillXP;
			break;

		case EKillXP::LONGSHOTKILL:
			return longShotKillXP;
			break;

		case EKillXP::GRENADEKILL:
			return grenadeKillXP;
			break;

		case EKillXP::VICTORY:
			return victoryXP;
			break;

		default:
			return 0;
	}
}

bool AHindWarfare_PS::IsDoubleKill(TArray<float> killTimeList) const
{
	if (killTimeList.Num() > 1)
	{
		int lastIndex = killTimeList.Num() - 1;
		float killDiff = 0;
		killDiff = killTimeList[lastIndex] - killTimeList[lastIndex - 1];
		return killDiff <= killLatency ? true : false;
	}
	return false;
}

bool AHindWarfare_PS::IsTripleKill(TArray<float> killTimeList) const
{
	if (killTimeList.Num() > 2)
	{
		int lastIndex = killTimeList.Num() - 1;
		float killDiff1 = 0, killDiff2 = 0;
		killDiff1 = killTimeList[lastIndex] - killTimeList[lastIndex - 1];
		killDiff2 = killTimeList[lastIndex - 1] - killTimeList[lastIndex - 2];
		return ((killDiff1 <= killLatency) && (killDiff2 <= killLatency) ? true : false);
	}
	return false;
}

bool AHindWarfare_PS::IsHeadKill(FName hitBoneName) const
{
	FName headBoneName("head");
	return headBoneName.IsEqual(hitBoneName);
}

bool AHindWarfare_PS::IsLongShotKill(FVector bulletImpactPoint, FVector gunNozlePos) const
{
	float longShotDistance = 2000;
	float distance;
	distance = FVector::Dist(bulletImpactPoint, gunNozlePos);

	return distance >= longShotDistance ? true : false;
}

bool AHindWarfare_PS::IsGrenadeKill() const
{
	return false;
}

bool AHindWarfare_PS::IsVictoryXP() const
{
	return false;
}

void AHindWarfare_PS::AddXP(int newXP)
{
	XPCount += newXP;
	maxXP = GetLevelMaxXP(currentLevel);
	if (XPCount >= maxXP)
	{
		XPCount -= maxXP;
		LevelUp();
	}

	UE_LOG(LogTemp, Warning, TEXT("oooo XP added = %d "), XPCount);
}

void AHindWarfare_PS::LevelUp()
{
	currentLevel = GetNextLevel(currentLevel);
}
