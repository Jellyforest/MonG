// Fill out your copyright notice in the Description page of Project Settings.


#include "MonGGameModeBase.h"
#include "Dust.h"
#include <Kismet/GameplayStatics.h>
#include "StartWidget.h"


void AMonGGameModeBase::BeginPlay()
{
	start_UI = CreateWidget<UStartWidget>(GetWorld(), startWidget);
	ShowStartUI();

}

void AMonGGameModeBase::AddScore(int32 score)
{
	dust = Cast<ADust>(UGameplayStatics::GetActorOfClass(GetWorld(), ADust::StaticClass()));
	//score = dust->point;
	currentScore += score;

}

void AMonGGameModeBase::ShowStartUI()
{
	if (start_UI != nullptr)
	{
		//생성된 위젯을 뷰포트에 그린다.

		start_UI->AddToViewport();
		isShowStartUI = true;
		UGameplayStatics::SetGamePaused(GetWorld(), true);

	}
}

