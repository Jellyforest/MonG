// Fill out your copyright notice in the Description page of Project Settings.


#include "PointWidget.h"
#include "Components/TextBlock.h"
#include "MonGGameModeBase.h"
#include "PlayWidget.h"
#include "Components/EditableText.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include <UMG/Public/Components/WidgetComponent.h>


void UPointWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Construct();
	UpdateCanTick();
}

void UPointWidget::Tick(float DeltaTime)
{

}

void UPointWidget::PrintingCurrentScore()
{
	auto monGgm = Cast<AMonGGameModeBase>(UGameplayStatics::GetGameMode(this));
	//auto playWidget = Cast<UPlayWidget>(UGameplayStatics::GetActorOfClass(GetWorld(), UPlayWidget::StaticClass()));
	if (monGgm)
	{
		UE_LOG(LogTemp, Warning, TEXT("printcurrentscore"));
		// ���� ����(����) -> FText (���ڿ�) ���·� ��ȯ�Ѵ�.
		FText scoreText = FText::AsNumber(monGgm->currentScore);
		//FText scoreText = playWidget->text_Score;
		currentScoreTB->SetText(scoreText);
		//currentScoreTB = playWidget->text_Score;


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
