// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreWidget.h"
#include <Kismet/GameplayStatics.h>
#include "Components/TextBlock.h"
#include "MonGGameModeBase.h"

void UScoreWidget::PrintCurrentScore()
{
	AMonGGameModeBase* monGgm = Cast<AMonGGameModeBase>(UGameplayStatics::GetGameMode(this));

	if (monGgm != nullptr)
	{
		// 현재 점수(정수) -> FText (문자열) 형태로 변환한다.
		//FText scoreText = FText::AsNumber(myGM->GetCurrentScore());
	}

	//curScore 텍스트 블록의 값으로 설정한다.
	//currentScoreTB->SetText(scoreText);

	/*
	// 순위점수 출력
	FText recordFirstText = FText::AsNumber(myGM->scoreFirst);
	FText recordSecondText = FText::AsNumber(myGM->scoreSecond);
	FText recordThirdText = FText::AsNumber(myGM->scoreThird);
	recordFirst->SetText(recordFirstText);
	recordSecond->SetText(recordSecondText);
	recordThird->SetText(recordThirdText);
	*/
}
