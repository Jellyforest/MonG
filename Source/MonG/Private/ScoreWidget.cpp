// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreWidget.h"
#include "Components/TextBlock.h"
#include "MonGGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "KeyboardWidget.h"
#include "KeyBoard.h"
#include <UMG/Public/Components/WidgetComponent.h>
#include "PlayWidget.h"
#include "PlayWidgetActor.h"



void UScoreWidget::NativeConstruct()
{
	Super::NativeConstruct();

	monGgm = Cast<AMonGGameModeBase>(GetWorld()->GetAuthGameMode());
	playWidgetActor = Cast<APlayWidgetActor>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayWidgetActor::StaticClass()));
	playWidget = Cast<UPlayWidget>(playWidgetActor->playWidgetComp->GetWidget());
	scoreTextArray = {recordFirst, recordSecond, recordThird, recordFourth, recordFifth, recordSixth, recordSeventh};
	idArray = { text_First, text_Second, text_Third, text_Fourth, text_Fifth, text_Sixth, text_Seventh };

}


void UScoreWidget::PrintCurrentScore()
{
	AKeyBoard* keyboard = Cast<AKeyBoard>(UGameplayStatics::GetActorOfClass(GetWorld(), AKeyBoard::StaticClass()));
	UKeyboardWidget* keyboardWidget = Cast<UKeyboardWidget>(keyboard->keyboardWidgetComp->GetWidget());


	if (monGgm != nullptr)
	{
		FText scoreText = FText::FromString(FString::Printf(TEXT("%d"), monGgm->currentScore));
		currentScoreTB->SetText(scoreText);

		FText iDText = FText::FromString(keyboardWidget->resultArray);
		currentText->SetText(iDText);
	}
//	auto dust = Cast<ADust>(UGameplayStatics::GetActorOfClass(GetWorld(), ADust::StaticClass()));
//	if(dust)
//	{
		// 현재 점수(정수) -> FText (문자열) 형태로 변환한다.
	

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


		// 순위점수 출력
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

void UScoreWidget::PrintRanking()
{
	for (int32 i = 0; i < scoreTextArray.Num(); i++)
	{
		if (monGgm->scoreArray.IsValidIndex(i))
		{
			scoreTextArray[i]->SetText(FText::FromString(FString::FromInt(monGgm->scoreArray[i])));
		}
	}
	for (int32 i = 0; i < idArray.Num(); i++)
	{
		if (monGgm->scoreIDArray.IsValidIndex(i))
		{
			idArray[i]->SetText((FText::FromString(monGgm->scoreIDArray[i])));
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
