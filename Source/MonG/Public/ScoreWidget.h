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

	virtual void NativeConstruct() override;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ScoreSettings", meta = (BindWidget))
	class UTextBlock* currentText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ScoreTextSettings", meta = (BindWidget))
	class UTextBlock* text_First;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ScoreTextSettings", meta = (BindWidget))
		class UTextBlock* text_Second;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ScoreTextSettings", meta = (BindWidget))
		class UTextBlock* text_Third;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ScoreTextSettings", meta = (BindWidget))
		class UTextBlock* text_Fourth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ScoreTextSettings", meta = (BindWidget))
		class UTextBlock* text_Fifth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ScoreTextSettings", meta = (BindWidget))
		class UTextBlock* text_Sixth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ScoreTextSettings", meta = (BindWidget))
		class UTextBlock* text_Seventh;


	//UPROPERTY()
//	class UPlayWidget* playWidget;
	//UPROPERTY()
	//class AMonGGameModeBase* monGgm;


	UFUNCTION()
	void PrintCurrentScore();
	
	UFUNCTION()
	void PrintRanking();

	UPROPERTY()
	class AMonGGameModeBase* monGgm;
	
	//게임플레위젯
	UPROPERTY()
	class UPlayWidget* playWidget;
	
	UPROPERTY()
	class APlayWidgetActor* playWidgetActor;

	TArray <UTextBlock*> scoreTextArray;
	TArray <UTextBlock*> idArray;

};
