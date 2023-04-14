// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DustSpawner.h"
#include "DustStrollSpawner.generated.h"

/**
 * 
 */
UCLASS()
class MONG_API ADustStrollSpawner : public ADustSpawner
{
	GENERATED_BODY()
	
public:
	ADustStrollSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float teleportTime = 0;
	float teleportTime1 = 7;
	float currentTime = 0;
	float moveSpeed = 30;
	FVector rightDirection;
	FVector leftDirection;

};
