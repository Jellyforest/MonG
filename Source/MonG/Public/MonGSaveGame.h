// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MonGSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class MONG_API UMonGSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UMonGSaveGame();

public:
	UPROPERTY(EditAnywhere,Category="SaveData")
	FString saveSlotName;
	UPROPERTY(EditAnywhere,Category="SaveData")
	int32 saveIndex;	



	UPROPERTY()
	TArray <int32> saveScoreArray;
};
