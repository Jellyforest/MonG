// Fill out your copyright notice in the Description page of Project Settings.


#include "MonGGameModeBase.h"
#include "Dust.h"
#include <Kismet/GameplayStatics.h>
#include "MonGSaveGame.h"
#include "ScoreWidgetActor.h"
#include "ScoreWidget.h"
#include <UMG/Public/Components/WidgetComponent.h>


void AMonGGameModeBase::BeginPlay()
{
	LoadScore();
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

		scoreDataInstance->saveScoreArray =scoreArray;

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
			scoreArray = loadDataInstance->saveScoreArray;
		}

	}

}

void AMonGGameModeBase::RecordScore()
{
	AScoreWidgetActor* scoreWidgetActor = Cast<AScoreWidgetActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AScoreWidgetActor::StaticClass()));
	UScoreWidget* scoreWidget = Cast<UScoreWidget>(scoreWidgetActor->scoreWidgetComp->GetWidget());

	if (scoreArray.Num() < 7)
	{
		// 무조건 더한다
		scoreArray.Add(currentScore);
		// 정렬한다
		scoreArray.Sort([](const int& A, const int& B) {
			return A > B;
			});
	}
	else
	{
		// 만약 랭킹의 꼴찌보다 잘했다면
		if (currentScore > scoreArray[scoreArray.Num() - 1])
		{
			// 하나 더하고
			scoreArray.Add(currentScore);
			// 정렬한다
			scoreArray.Sort([](const int& A, const int& B) {
				return A > B;
				});
			// 꼴찌 하나 뺀다
			UE_LOG(LogTemp, Warning, TEXT("%d"), scoreArray.Num());
			scoreArray.RemoveAt(scoreArray.Num()-1, 1, false);
		}
	}

	SaveScore();
	scoreWidget->PrintRanking();

}


















































































































































































