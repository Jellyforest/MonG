// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayWidget.h"
#include <Kismet/KismetTextLibrary.h>
#include "Components/TextBlock.h"
#include <Engine/World.h>
#include "Kismet/GameplayStatics.h"

void UPlayWidget::GameTime()
{
	//timer += GetWorld()->DeltaTimeSeconds;
	//float Minute=(300 - timer) / 60;
	FTimerHandle countTime;
	FTimerDelegate timerDelegate;
	timerDelegate.BindLambda([this]()->void {
		timer -= 1; minute = timer / 60; second = timer % 60;
		});
	GetWorld()->GetTimerManager().SetTimer(countTime, timerDelegate, 1, true);
	
}

