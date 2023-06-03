// Fill out your copyright notice in the Description page of Project Settings.


#include "MonGGameModeBase.h"
#include "Dust.h"
#include <Kismet/GameplayStatics.h>
#include "StartWidget.h"
#include "EndingWidget.h"
#include "MonGSaveGame.h"


void AMonGGameModeBase::BeginPlay()
{
	//start_UI = CreateWidget<UStartWidget>(GetWorld(), startWidget);
	//ending_UI = CreateWidget<UEndingWidget>(GetWorld(), endingWidget);
	ShowStartUI();

}

void AMonGGameModeBase::AddScore(int32 score)
{
	//dust = Cast<ADust>(UGameplayStatics::GetActorOfClass(GetWorld(), ADust::StaticClass()));
	//score = dust->point;
	currentScore += score;
}

void AMonGGameModeBase::ShowStartUI()
{
	//if (start_UI != nullptr)
	//{
		//생성된 위젯을 뷰포트에 그린다.

		//start_UI->AddToViewport();
		//isShowStartUI = true;
		//UGameplayStatics::SetGamePaused(GetWorld(), true);
	
	//}
}

void AMonGGameModeBase::ShowEndingUI()
{
	//if (ending_UI != nullptr)
	//{
	//	//ending_UI->AddToViewport();
		//isShowEndingUI = true;
		//UGameplayStatics::SetGamePaused(GetWorld(), true);

	//}
}

void AMonGGameModeBase::SaveScore()
{
	UMonGSaveGame* scoreDataInstance = Cast<UMonGSaveGame>(UGameplayStatics::CreateSaveGameObject(UMonGSaveGame::StaticClass()));
	if (scoreDataInstance)
	{
		scoreDataInstance->saveSlotName = "ScoreData";
		scoreDataInstance->saveIndex = 0;

		firstScore = scoreDataInstance->firstScore;
		secondScore = scoreDataInstance->secondScore;
		thirdScore = scoreDataInstance->thirdScore;
		fourthScore = scoreDataInstance->fourthScore;
		fifthScore = scoreDataInstance->fifthScore;
		sixthScore = scoreDataInstance->sixthScore;
		seventhScore = scoreDataInstance->seventhScore;
	}
}

void AMonGGameModeBase::LoadScore()
{
	UMonGSaveGame* loadDataInstance = Cast<UMonGSaveGame>(UGameplayStatics::CreateSaveGameObject(UMonGSaveGame::StaticClass()));
	if (loadDataInstance)
	{
		loadDataInstance->saveSlotName = "ScoreData";
		loadDataInstance->saveIndex = 0;

		loadDataInstance = Cast<UMonGSaveGame>(UGameplayStatics::LoadGameFromSlot(loadDataInstance->saveSlotName, loadDataInstance->saveIndex));
		if (loadDataInstance)
		{
			firstScore = loadDataInstance->firstScore;
			secondScore = loadDataInstance->secondScore;
			thirdScore = loadDataInstance->thirdScore;
			fourthScore = loadDataInstance->fourthScore;
			fifthScore = loadDataInstance->fifthScore;
			sixthScore = loadDataInstance->sixthScore;
			seventhScore = loadDataInstance->seventhScore;
		}

	}

}
























/*
if (currentScore >= firstScore)
{
	sixthScore = seventhScore;
	fifthScore = sixthScore;
	fourthScore = fifthScore;
	thirdScore = fourthScore;
	secondScore = firstScore;
	firstScore = currentScore;
}
else if (firstScore < currentScore && currentScore >= secondScore)
{
	sixthScore = seventhScore;
	fifthScore = sixthScore;
	fourthScore = fifthScore;
	thirdScore = fourthScore;
	secondScore = currentScore;
}
else if (secondScore < currentScore && currentScore >= thirdScore)
{
	sixthScore = seventhScore;
	fifthScore = sixthScore;
	fourthScore = fifthScore;
	thirdScore = currentScore;
}
//else if (thirdScore<currentScore>=fourthScore)
*/