// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ScoreWidgetActor.generated.h"

UCLASS()
class MONG_API AScoreWidgetActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AScoreWidgetActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ScoreWidgetSettings")
	TSubclassOf <class UScoreWidget> scoreWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ScoreWidgetSettings")
	class UScoreWidget* score_UI;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ScoreWidgetSettings")
	class UWidgetComponent* scoreWidgetComp;

};
