// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayWidget.h"
#include "Components/TextBlock.h"



void UPlayWidget::NativeConstruct()
{
	UpdateCanTick();
	FTimerHandle countTime;
	FTimerDelegate timerDelegate;
	timerDelegate.BindLambda([this]()->void {
		timer -= 1; minute = timer / 60; second = timer % 60;
	text_Minute->SetText(FText::FromString(FString::Printf(TEXT("0%d"), minute)));
	text_Second->SetText(FText::FromString(FString::Printf(TEXT("%d"), second)));
		});
	GetWorld()->GetTimerManager().SetTimer(countTime, timerDelegate, 1, true);
}

void UPlayWidget::UpdateCanTick()
{
	
}
