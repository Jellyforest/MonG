// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Postit.generated.h"

UCLASS()
class MONG_API APostit : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APostit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Postit Settings")
	class UMaterial* markerInk;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Postit Settings")
	class UCanvasRenderTarget2D* postitLander;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Postit Settings")
	class UMaterialInstanceDynamic* boardMarker;
	UPROPERTY()
	class AMarker* marker;

	UFUNCTION()
	void Drawing();
	UFUNCTION()
	void DrawSize(float drawSize);
	UPROPERTY()
	FVector endPos;
	UPROPERTY()
	FVector startPos;
	FName drawLocation;
	FName drawSizePram;
	//FVector2D locationToDraw;

};
