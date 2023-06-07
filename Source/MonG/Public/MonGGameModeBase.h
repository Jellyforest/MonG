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

protected:
	virtual void BeginPlay() override;

public:

	UPROPERTY()
	class ADust* dust;
	UPROPERTY()
	class AScoreWidgetActor* scoreWidgetActor;
	UPROPERTY()
	class UScoreWidget* scoreWidget;

	//먼지점수
	void AddScore(int32 score);
	
	
	//점수 저장
	void SaveScore();
	void LoadScore();

	FORCEINLINE int32 GetCurrentScore() { return currentScore; }


	//현재점수
	int32 currentScore;
	int32 firstScore;
	int32 secondScore;
	int32 thirdScore;
	int32 fourthScore;
	int32 fifthScore;
	int32 sixthScore;
	int32 seventhScore;
	

	TArray <int32> scoreArray;
	TArray <FString> scoreIDArray;
	TMap <FString, int32> rankingMap;

	
	void PlusRanking(FString scoreID);
	void RankingData();
	
};
