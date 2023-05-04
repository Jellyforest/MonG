// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cleaner.generated.h"

UCLASS()
class MONG_API ACleaner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACleaner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,Category="CleanerSettings")
	class UStaticMeshComponent* cleanerMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,Category="CleanerSettings")
	class UBoxComponent* cleanerComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,Category="CleanerSettings")
	class UStaticMeshComponent* cleanerHead;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,Category="CleanerSettings")
	class USphereComponent* cleanerHeadComp;
	//청소FX
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CleanerSettings")
	TSubclassOf <class ACleaningEffect> cleaningEffect;

	void CleanerClean();
	UFUNCTION()
	void OnCleanerComp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//먼지
	class ADust* dust;
	class AMonGPlayer* monGPlayer;

};
