// Fill out your copyright notice in the Description page of Project Settings.


#include "MonGGameModeBase.h"
#include "Dust.h"
#include <Kismet/GameplayStatics.h>
#include "MonGSaveGame.h"
#include "ScoreWidgetActor.h"
#include "ScoreWidget.h"
#include <UMG/Public/Components/WidgetComponent.h>
#include "KeyboardWidget.h"
#include "KeyBoard.h"
#include "Components/TextBlock.h"
#include "PlayWidget.h"


void AMonGGameModeBase::BeginPlay()
{
	LoadScore();
	scoreWidgetActor = Cast<AScoreWidgetActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AScoreWidgetActor::StaticClass()));
	scoreWidget = Cast<UScoreWidget>(scoreWidgetActor->scoreWidgetComp->GetWidget());
}


void AMonGGameModeBase::AddScore(int32 score)
{
	//dust = Cast<ADust>(UGameplayStatics::GetActorOfClass(GetWorld(), ADust::StaticClass()));
	//score = dust->point;
	currentScore += score;
	//UE_LOG(LogTemp, Warning, TEXT("GameModeBase SCORE : %d"), currentScore);
}


void AMonGGameModeBase::SaveScore()
{
	UMonGSaveGame* scoreDataInstance = Cast<UMonGSaveGame>(UGameplayStatics::CreateSaveGameObject(UMonGSaveGame::StaticClass()));
	if (scoreDataInstance)
	{
		scoreDataInstance->saveSlotName = "ScoreData";
		scoreDataInstance->saveIndex = 0;

		scoreDataInstance->rankingMap =rankingMap;

		UGameplayStatics::SaveGameToSlot(scoreDataInstance, scoreDataInstance->saveSlotName, scoreDataInstance->saveIndex);
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
			rankingMap = loadDataInstance->rankingMap;
		}

	}

}




void AMonGGameModeBase::PlusRanking(FString scoreID)
{
	AKeyBoard* keyboard = Cast<AKeyBoard>(UGameplayStatics::GetActorOfClass(GetWorld(), AKeyBoard::StaticClass()));
	UKeyboardWidget* keyboardWidget = Cast<UKeyboardWidget>(keyboard->keyboardWidgetComp->GetWidget());

	if (scoreArray.Num() < 7)
	{	
		scoreID = keyboardWidget->resultArray;

		rankingMap.Add(scoreID, currentScore);
		rankingMap.ValueSort([](const int& A, const int& B) {
			return A > B;
			});
	}
	else if (currentScore > scoreArray[scoreArray.Num() - 1])
	{
		rankingMap.Add(scoreID, currentScore);
		rankingMap.ValueSort([](const int& A, const int& B) {
			return A > B;
			});
		rankingMap.GenerateKeyArray(scoreIDArray);
			
		// 맨 꼴찌 key를 알아낸다
		FString lastRankedName = scoreIDArray[scoreIDArray.Num() - 1];

		rankingMap.Remove(lastRankedName);
		
	}
	
	RankingData();
	SaveScore();

}

void AMonGGameModeBase::RankingData()
{
	scoreArray.Empty();
	scoreIDArray.Empty();

	rankingMap.GenerateValueArray(scoreArray);
	rankingMap.GenerateKeyArray(scoreIDArray);

	for (int32 i = 0; i < scoreWidget->scoreTextArray.Num(); i++)
	{
		if (scoreArray.IsValidIndex(i))
		{
			scoreWidget->scoreTextArray[i]->SetText(FText::FromString(FString::FromInt(scoreArray[i])));
		}
	}
	for (int32 i = 0; i < scoreWidget->idArray.Num(); i++)
	{
		if (scoreIDArray.IsValidIndex(i))
		{
			scoreWidget->idArray[i]->SetText((FText::FromString(scoreIDArray[i])));
		}
	}
	scoreWidget->PrintRanking();

}


















































































































































































