// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Dust.h"
#include "MonGGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MONG_API AMonGGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY()
	class ADust* dust;
	void AddScore(int32 score);
	int32 currentScore;
	
};
