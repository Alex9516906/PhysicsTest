﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "TestBasePlatform.generated.h"

UCLASS()
class TEST_API ATestBasePlatform : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	
	ATestBasePlatform();

protected:
	
	virtual void Tick(float DeltaSeconds) override;
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void SetVelocity();
	
	FTimerHandle TimerSetVelocityRotation;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	float RateSpeedTimerVelocity = 0.1f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	FVector NewAngVelocityBarrier = FVector(0.f,0.f,3.f);

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	float StrengthImpulse = 500;
	
	UFUNCTION()
	void OnBarrierComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:

	void StartPlay();
};

