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

	UPROPERTY(EditAnywhere,Category="ScoreSettings")
	int32 currentScore;
	UPROPERTY(EditAnywhere,Category="ScoreSettings")
	int32 firstScore;
	UPROPERTY(EditAnywhere,Category="ScoreSettings")
	int32 secondScore;
	UPROPERTY(EditAnywhere,Category="ScoreSettings")
	int32 thirdScore;
	UPROPERTY(EditAnywhere,Category="ScoreSettings")
	int32 fourthScore;
	UPROPERTY(EditAnywhere,Category="ScoreSettings")
	int32 fifthScore;
	UPROPERTY(EditAnywhere,Category="ScoreSettings")
	int32 sixthScore;
	UPROPERTY(EditAnywhere,Category="ScoreSettings")
	int32 seventhScore;
	UPROPERTY(EditAnywhere,Category="ScoreSettings")
	FString saveSlotName;
	UPROPERTY(EditAnywhere,Category="ScoreSettings")
	int32 saveIndex;	


};
