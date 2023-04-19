// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayWidget.h"
#include <Kismet/KismetTextLibrary.h>
#include "Components/TextBlock.h"


void UPlayWidget::GameTime(float timer)
{
	text_Minute->SetText(UKismetTextLibrary::Conv_IntToText((int)timer / 60));
	text_Second->SetText(UKismetTextLibrary::Conv_IntToText((150 - (int)timer) % 60));
}
