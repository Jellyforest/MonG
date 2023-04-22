// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayWidget.h"
#include <Kismet/KismetTextLibrary.h>
#include "Components/TextBlock.h"
#include <Engine/World.h>
#include "Kismet/GameplayStatics.h"

void UPlayWidget::GameTime()
{
	//FTimerHandle countTime;
	//FTimerDelegate timerDelegate;
	//timerDelegate.BindLambda([this]()->void {
	//	timer -= 1; minute = timer / 60; second = timer % 60;
	//	});
	//	GetWorld()->GetTimerManager().SetTimer(countTime, timerDelegate, 1, true);
	//	UE_LOG(LogTemp, Warning, TEXT("%s"), minute);
	
	FText minutetext = FText::AsNumber(minute);

	//UE_LOG(LogTemp, Warning, TEXT("%d"), minutetext);
	text_Minute->SetText(minutetext);
}

