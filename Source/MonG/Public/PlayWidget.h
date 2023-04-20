// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayWidget.generated.h"

/**
 * 
 */
UCLASS()
class MONG_API UPlayWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* text_Minute;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* text_Second;
	
	void GameTime(float Timer);

};