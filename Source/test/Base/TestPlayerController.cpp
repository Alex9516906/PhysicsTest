// Fill out your copyright notice in the Description page of Project Settings.


#include "TestPlayerController.h"

#include "TestGameMode.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

ATestPlayerController::ATestPlayerController()
{

	PrimaryActorTick.bCanEverTick = true;
}

void ATestPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATestPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATestPlayerController::Server_SetPosition_Implementation()
{
	if(ATestGameMode* GM = Cast<ATestGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		if(APlayerStart* PS = GM->GetRandomPlayerStart())
		GetCharacter()->SetActorTransform(PS->GetActorTransform());
	}
}

