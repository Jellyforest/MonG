// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreWidget.h"
#include "Components/TextBlock.h"
#include "MonGGameModeBase.h"
#include "Kismet/GameplayStatics.h"



void UScoreWidget::NativeConstruct()
{
	Super::NativeConstruct();

	monGgm = Cast<AMonGGameModeBase>(GetWorld()->GetAuthGameMode());

	scoreTextArray = {recordFirst, recordSecond, recordThird, recordFourth, recordFifth, recordSixth, recordSeventh};


}


void UScoreWidget::PrintCurrentScore()
{

	if (monGgm != nullptr)
	{
		FText scoreText = FText::AsNumber(monGgm->currentScore);
		currentScoreTB->SetText(scoreText);

	}
//	auto dust = Cast<ADust>(UGameplayStatics::GetActorOfClass(GetWorld(), ADust::StaticClass()));
//	if(dust)
//	{
		// ���� ����(����) -> FText (���ڿ�) ���·� ��ȯ�Ѵ�.
	

		//currentScoreTB->SetText(scoreText);
//	}
	//monGgm->MyGetWorld();
	//if (monGgm)
	//{
			//auto playWidget = Cast<UPlayWidget>(UGameplayStatics::GetActorOfClass(GetWorld(), UPlayWidget::StaticClass()));
		//	UE_LOG(LogTemp, Warning, TEXT("printcurrentscore"));
			
			//FText scoreText = playWidget->text_Score;
			//currentScoreTB->SetText(scoreText);
			//currentScoreTB = playWidget->text_Score;

	//}


		// �������� ���
	/*
		FText recordFirstText = FText::AsNumber(monGgm->firstScore);
		FText recordSecondText = FText::AsNumber(monGgm->secondScore);
		FText recordThirdText = FText::AsNumber(monGgm->thirdScore);
		FText recordFourthText = FText::AsNumber(monGgm->fourthScore);
		FText recordFifthText = FText::AsNumber(monGgm->fifthScore);
		FText recordSixthText = FText::AsNumber(monGgm->sixthScore);
		FText recordSeventhText = FText::AsNumber(monGgm->seventhScore);
		recordFirst->SetText(recordFirstText);
		recordSecond->SetText(recordSecondText);
		recordThird->SetText(recordThirdText);
		recordFourth->SetText(recordFourthText);
		recordFifth->SetText(recordFifthText);
		recordSixth->SetText(recordSixthText);
		recordSeventh->SetText(recordSeventhText);
		*/
	

	
		

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

void UScoreWidget::PrintRanking()
{
	for (int i = 0; i < scoreTextArray.Num(); i++)
	{
		if (monGgm->scoreArray.IsValidIndex(i))
		{
			scoreTextArray[i]->SetText(FText::FromString(FString::FromInt(monGgm->scoreArray[i])));
		}
	}

	/*
	FText recordFirstText = FText::AsNumber(monGgm->scoreArray[0]);
	recordFirst->SetText(recordFirstText);
	if (monGgm->scoreArray.IsValidIndex(1))
	{
		FText recordSecondText = FText::AsNumber(monGgm->scoreArray[1]);
		recordSecond->SetText(recordSecondText);
	}

	FText recordThirdText = FText::AsNumber(monGgm->scoreArray[2]);
	FText recordFourthText = FText::AsNumber(monGgm->scoreArray[3]);
	FText recordFifthText = FText::AsNumber(monGgm->scoreArray[4]);
	FText recordSixthText = FText::AsNumber(monGgm->scoreArray[5]);
	FText recordSeventhText = FText::AsNumber(monGgm->scoreArray[6]);

	recordThird->SetText(recordThirdText);
	recordFourth->SetText(recordFourthText);
	recordFifth->SetText(recordFifthText);
	recordSixth->SetText(recordSixthText);
	recordSeventh->SetText(recordSeventhText);
	recordFirst->SetText(recordFirstText);
	*/
}
