// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MonGPlayer.h"
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


	//먼지생성
	UPROPERTY(EditAnywhere)
	class USphereComponent* dustComp;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* dustMesh;
	//먼지 날아오는 속도
	//float moveSpeed = 5;
	float moveSpeed = 500;
	//먼지 방향
	FVector monGDirection;
	//시간이 지나면 먼지 삭제
	float destroyTime = 3.5f;
	float currentTime = 0;
	UPROPERTY()
	AMonGPlayer* monGPlayer;
	
	UPROPERTY(EditAnywhere,Category="Score Settings")
	int32 point;
	bool getPoint=false;

};
