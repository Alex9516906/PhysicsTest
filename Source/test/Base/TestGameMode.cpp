#include "TestGameMode.h"

#include "TestPlayerStart.h"
#include "GameFramework/GameSession.h"
#include "Kismet/KismetMathLibrary.h"


ATestGameMode::ATestGameMode()
{

	PrimaryActorTick.bCanEverTick = true;
	
}

void ATestGameMode::BeginPlay()
{
	Super::BeginPlay();
	GameSession->MaxPlayers = 2;
}

void ATestGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	
	if(!NewPlayer){return;}

	if(IsFirstPlayer())
	{
		GEngine->AddOnScreenDebugMessage(-1,10.f,FColor::Green,FString::Printf(TEXT("%s Please wait for the second player"),
			*NewPlayer->GetName()));
	}
	else
	{
		GEngine->ClearOnScreenDebugMessages();
		OnStartPlatformDelegate.Broadcast();
	}
	
	if(CurrentNumberOfPlayers<GameSession->MaxPlayers )
	{
		PlayerControllers.Add(NewPlayer);
		CurrentNumberOfPlayers++;
	}
	else
	{
		GameSession->KickPlayer(NewPlayer, FText::FromString(TEXT("Maximum number of players reached")));
	}
}

void ATestGameMode::AddToPlayerStart(APlayerStart* NewPlayerStart)
{
	if(ATestPlayerStart* Ps = Cast<ATestPlayerStart>(NewPlayerStart))
		PlayerStarts.Add(Ps);
}

APlayerStart* ATestGameMode::GetRandomPlayerStart()
{
	int32 RandomInt = UKismetMathLibrary::RandomInteger(PlayerStarts.Num());
	return PlayerStarts[RandomInt];
}


bool ATestGameMode::IsFirstPlayer()
{
	if(CurrentNumberOfPlayers<1)
	{
		return true;
	}
	return false;
}


