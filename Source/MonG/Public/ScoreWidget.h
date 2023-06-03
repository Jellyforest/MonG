// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreWidget.generated.h"

/**
 * 
 */
UCLASS()
class MONG_API UScoreWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ScoreSettings", meta = (BindWidget))
	class UTextBlock* currentScoreTB;
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

	
	void PrintCurrentScore();


};
