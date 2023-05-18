// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayWidget.h"
#include "Components/TextBlock.h"
#include "MonGGameModeBase.h"
#include <Kismet/GameplayStatics.h>
#include "MonGPlayer.h"



void UPlayWidget::NativeConstruct()
{
	monGPlayer = Cast<AMonGPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), AMonGPlayer::StaticClass()));

	Construct();
	UpdateCanTick();
	FTimerHandle countTime;
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
			AGameModeBase* gm = UGameplayStatics::GetGameMode(this);
			AMonGGameModeBase* monGgm = Cast<AMonGGameModeBase>(gm);
			timer = 0;
			monGgm->ShowEndingUI();
		}
		
		});
	GetWorld()->GetTimerManager().SetTimer(countTime, timerDelegate, 1, true);

	//����
	FTimerHandle countScore;
	FTimerDelegate timerDelegate1;
	timerDelegate1.BindLambda([this]()->void {
		AGameModeBase* gm = UGameplayStatics::GetGameMode(this);
	AMonGGameModeBase* monGgm = Cast<AMonGGameModeBase>(gm);
	text_Score->SetText(FText::FromString(FString::Printf(TEXT("%d"), monGgm->currentScore))); });
	GetWorld()->GetTimerManager().SetTimer(countScore, timerDelegate1, 0.01, true);

}

void UPlayWidget::Tick(float DeltaTime)
{
	/*
	AGameModeBase* gm = UGameplayStatics::GetGameMode(this);
	AMonGGameModeBase* monGgm = Cast<AMonGGameModeBase>(gm);
	text_Score->SetText(FText::FromString(FString::Printf(TEXT("%d"), monGgm->currentScore)));
	*/
}

