// Fill out your copyright notice in the Description page of Project Settings.


#include "TestPlayerStart.h"

#include "TestGameMode.h"
#include "Kismet/GameplayStatics.h"

void ATestPlayerStart::BeginPlay()
{
	Super::BeginPlay();
	if(ATestGameMode* GM = Cast<ATestGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		GM->AddToPlayerStart(this);
	}
}
