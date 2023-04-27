// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Dust.h"
#include "DustSpawner.generated.h"

UCLASS()
class MONG_API ADustSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADustSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "SpawnerSettings")
	class UStaticMeshComponent* spawnerMesh;
	UPROPERTY(EditAnywhere, Category = "SpawnerSettings")
	class UBoxComponent* spawnerComp;
	UPROPERTY(EditAnywhere, Category = "SpawnerSettings")
	class UArrowComponent* arrow;
	float coolTime = 1;
	float currentTime = 0;
	UPROPERTY(EditAnywhere, Category = "SpawnerSettings")
	TSubclassOf <ADust> dustSpawn;
	
	UPROPERTY(EditAnywhere, Category = "SpawnerSettings")
	TSubclassOf <ADust> dustP3Spawn;

	UPROPERTY(EditAnywhere, Category = "SpawnerSettings")
	TSubclassOf <ADust> dustP4Spawn;


	int32 pointThree = 30;
	int32 pointFive = 10;
};
