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
		// ���� ����(����) -> FText (���ڿ�) ���·� ��ȯ�Ѵ�.
		//FText scoreText = FText::AsNumber(myGM->GetCurrentScore());
	}

	//curScore �ؽ�Ʈ ����� ������ �����Ѵ�.
	//currentScoreTB->SetText(scoreText);

	/*
	// �������� ���
	FText recordFirstText = FText::AsNumber(myGM->scoreFirst);
	FText recordSecondText = FText::AsNumber(myGM->scoreSecond);
	FText recordThirdText = FText::AsNumber(myGM->scoreThird);
	recordFirst->SetText(recordFirstText);
	recordSecond->SetText(recordSecondText);
	recordThird->SetText(recordThirdText);
	*/
}
