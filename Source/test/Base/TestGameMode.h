#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TestGameMode.generated.h"

class APlayerStart;

DECLARE_MULTICAST_DELEGATE(FOnStartPlatform)

UCLASS()
class TEST_API ATestGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	ATestGameMode();

protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	int32 MaxPlayers;

	int32 CurrentNumberOfPlayers = 0;

	UPROPERTY()
	TArray<APlayerController*> PlayerControllers;

	bool IsFirstPlayer();

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	TArray<APlayerStart*> PlayerStarts;

public:

	virtual void PostLogin(APlayerController* NewPlayer) override;

	void AddToPlayerStart(APlayerStart* NewPlayerStart);

	TArray<APlayerStart*>& GetPlayerStarts(){return PlayerStarts;}

	APlayerStart* GetRandomPlayerStart();

	FOnStartPlatform OnStartPlatformDelegate;
};
