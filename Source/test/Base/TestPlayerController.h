// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestPlayerController.generated.h"

UCLASS()
class TEST_API ATestPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	
	ATestPlayerController();

protected:
	
	virtual void BeginPlay() override;

public:
	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(Server,Reliable)
	void Server_SetPosition();
};
