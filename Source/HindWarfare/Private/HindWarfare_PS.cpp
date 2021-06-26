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

bool AHindWarfare_PS::IsDoubleKill(int firstKillTime, int secondKillTime) const
{
	return (secondKillTime - firstKillTime) <= killLatency ? true : false;
}

bool AHindWarfare_PS::IsTripleKill(int firstKillTime, int secondKillTime, int thirdKillTime) const
{
	if ((thirdKillTime - secondKillTime) <= killLatency && (secondKillTime - firstKillTime) <= killLatency)
	{
		return true;
	}
	return false;
}

bool AHindWarfare_PS::IsHeadKill(FVector headVect, FVector bulletImpactPoint) const
{
	float headShotBuffer = 10.0f;
	return headVect.Equals(bulletImpactPoint,headShotBuffer);
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
