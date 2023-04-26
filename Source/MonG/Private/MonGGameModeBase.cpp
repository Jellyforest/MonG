// Fill out your copyright notice in the Description page of Project Settings.


#include "MonGGameModeBase.h"
#include "Dust.h"
#include <Kismet/GameplayStatics.h>

void AMonGGameModeBase::AddScore()
{
	//����
	ADust* dust = Cast<ADust>(UGameplayStatics::GetActorOfClass(GetWorld(), ADust::StaticClass()));

	int32 count = dust->onePointScore;
	int32 count1 = dust->threePointScore;
	currentScore += count1;
}
 