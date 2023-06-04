// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PointWidget.generated.h"

/**
 * 
 */
UCLASS()
class MONG_API UPointWidget : public UUserWidget
{
	GENERATED_BODY()
	public:

	virtual void NativeConstruct() override;
	virtual void Tick(float DeltaTime);

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ScoreSettings", meta = (BindWidget))
	class UTextBlock* currentScoreTB;
	/*
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ScoreSettings", meta = (BindWidget))
	class UTextBlock* recordFirst;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ScoreSettings", meta = (BindWidget))
	class UTextBlock* recordSecond;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ScoreSettings", meta = (BindWidget))
	class UTextBlock* recordThird;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ScoreSettings", meta = (BindWidget))
	class UTextBlock* recordFourth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ScoreSettings", meta = (BindWidget))
	class UTextBlock* recordFifth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ScoreSettings", meta = (BindWidget))
	class UTextBlock* recordSixth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ScoreSettings", meta = (BindWidget))
	class UTextBlock* recordSeventh;
	*/

	//UPROPERTY()
//	class UPlayWidget* playWidget;
	//UPROPERTY()
	//class AMonGGameModeBase* monGgm;


	UFUNCTION()
	void PrintingCurrentScore();


};
