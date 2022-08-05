// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "TestPlayerStart.generated.h"

/**
 * 
 */
UCLASS()
class TEST_API ATestPlayerStart : public APlayerStart
{
	GENERATED_BODY()
	
	protected:
	virtual void BeginPlay() override;
};
