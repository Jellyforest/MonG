// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Dust.generated.h"

UCLASS()
class MONG_API ADust : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADust();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	class USphereComponent* dustComp;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* dustMesh;


};
