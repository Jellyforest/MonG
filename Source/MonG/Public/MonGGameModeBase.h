// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Dust.h"
#include "MonGGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MONG_API AMonGGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:

	UPROPERTY()
	class ADust* dust;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WidgetSettings")
	TSubclassOf<class UStartWidget> startWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WidgetSettings")
	TSubclassOf<class UEndingWidget> endingWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WidgetSettings")
	class UStartWidget* start_UI;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WidgetSettings")
	class UEndingWidget* ending_UI;


	//먼지점수
	void AddScore(int32 score);

	//위젯
	void ShowStartUI();
	void ShowEndingUI();

	//현재점수
	int32 currentScore;

	

	bool isShowStartUI = false;
	bool isShowEndingUI = false;
	
};
