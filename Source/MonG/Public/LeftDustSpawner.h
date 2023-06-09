// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Dust.h"
#include "LeftDustSpawner.generated.h"

UCLASS()
class MONG_API ALeftDustSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALeftDustSpawner();

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
	float coolTime = 0.5;
	float coolCurentTime = 0;
	UPROPERTY(EditAnywhere, Category = "SpawnerSettings")
	TSubclassOf <ADust> dustSpawn;


	float teleportTime = 1;
	float teleportTime1 = 6;

	float currentTime = 0;
	float moveSpeed = 3;
	float fire = 10;
	float fireTime = 0;

};
