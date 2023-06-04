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



	//��������
	void AddScore(int32 score);
	
	
	//����
	void SaveScore();
	void LoadScore();

	FORCEINLINE int32 GetCurrentScore() { return currentScore; }


	//��������
	int32 currentScore;
	int32 firstScore;
	int32 secondScore;
	int32 thirdScore;
	int32 fourthScore;
	int32 fifthScore;
	int32 sixthScore;
	int32 seventhScore;

	UFUNCTION(BlueprintCallable)
    static UWorld* MyGetWorld();
	
};
