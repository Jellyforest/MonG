// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorStartWidget.generated.h"

UCLASS()
class MONG_API AActorStartWidget : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActorStartWidget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StartWidget")
	TSubclassOf <class UStartWidget> startWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StartWidget")
	class UStartWidget* start_UI;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StartWidget")
	class UWidgetComponent* startWidgetComp;


	bool isShowStartUI = false;
};
