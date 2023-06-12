// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayWidget.h"
#include "Components/TextBlock.h"
#include "MonGGameModeBase.h"
#include <Kismet/GameplayStatics.h>
#include "MonGPlayer.h"
#include "EndingWidget.h"
#include <UMG/Public/Components/WidgetComponent.h>
#include "ScoreWidget.h"
#include "ScoreWidgetActor.h"
#include "PointWidget.h"



void UPlayWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Construct();
	UpdateCanTick();

	monGPlayer = Cast<AMonGPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), AMonGPlayer::StaticClass()));
	monGgm = Cast<AMonGGameModeBase>(UGameplayStatics::GetGameMode(this));
	/////////scoreWidget = Cast<UScoreWidget>(UGameplayStatics::GetActorOfClass(GetWorld(), UScoreWidget::StaticClass()));
	scoreWidgetActor = Cast<AScoreWidgetActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AScoreWidgetActor::StaticClass()));
	///////////////pointWidget = Cast<UPointWidget>(UGameplayStatics::GetActorOfClass(GetWorld(), UPointWidget::StaticClass()));

	
	FTimerDelegate timerDelegate;
	timerDelegate.BindLambda([this]()->void {
		if (timer > 0 && monGPlayer->isGameStart == true)
		{
			timer -= 1; minute = timer / 60; second = timer % 60;
			text_Minute->SetText(FText::FromString(FString::Printf(TEXT("0%d"), minute)));
			text_Second->SetText(FText::FromString(FString::Printf(TEXT("%d"), second)));
		}
		else if (timer == 0)
		{
			if (isEnd == false)
			{
				monGPlayer->GameEnding();
				monGPlayer->isGameStart = false;
			//	UE_LOG(LogTemp, Warning, TEXT(" Player Widget isGameStart : %d"), monGPlayer->isGameStart)
				isEnd = true;
				timer = 0;
				GetWorld()->GetTimerManager().ClearTimer(countScore);
				GetWorld()->GetTimerManager().ClearTimer(countTime);
			}

		}
		
		});
	GetWorld()->GetTimerManager().SetTimer(countTime, timerDelegate, 1, true);

	//Á¡¼ö
	FTimerDelegate timerDelegate1;
	timerDelegate1.BindLambda([this]()->void {
		
	text_Score->SetText(FText::FromString(FString::Printf(TEXT("%d"), monGgm->currentScore))); });
	GetWorld()->GetTimerManager().SetTimer(countScore, timerDelegate1, GetWorld()->GetDeltaSeconds(), true);

}

void UPlayWidget::Tick(float DeltaTime)
{
	/*
	AGameModeBase* gm = UGameplayStatics::GetGameMode(this);
	AMonGGameModeBase* monGgm = Cast<AMonGGameModeBase>(gm);
	text_Score->SetText(FText::FromString(FString::Printf(TEXT("%d"), monGgm->currentScore)));
	*/
}


