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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category="CleanerSettings")
	class UStaticMeshComponent* cleanerMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category="CleanerSettings")
	class UBoxComponent* cleanerComp;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category="CleanerSettings")
	class UStaticMeshComponent* cleanerHead;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category="CleanerSettings")
	class USphereComponent* cleanerHeadComp;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category="CleanerSettings")
	class UBoxComponent* cleanerStick;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CleanerSettings")
	TSubclassOf <class ACleaningEffect> cleaningEffect;
	
	//waterBullet
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "WaterBulletSettings")
	class UArrowComponent* arrow;
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "WaterBulletSettings")
	TSubclassOf<class AWaterBullet> waterBullet;
	//UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "WaterBulletSettings")
	//class UAudioComponent* bubbleSound;
	
	UFUNCTION()
	void CleaningTime(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintCallable, Category = "WaterBulletSettings")
	void Shoot();

	
	UPROPERTY()
	class AMonGPlayer* monGPlayer;
	UPROPERTY()
	class ADust* dust;
	UPROPERTY()
	class AMonGGameModeBase* monGgm;

	FVector monGDirection;
	bool isShoot = false;

	int32 bullet = 15;

	//UPROPERTY(EditDefaultsOnly, Category = cleanerSound)
	///class USoundCue* bubleSound;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = cleanerSound)
	class USoundBase* bubbleSoundBase;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = cleanerSound)
	class UAudioComponent* cleanerSoundComp;
	
	UPROPERTY(EditDefaultsOnly, Category = cleanerSound)
	class UAudioComponent* cleanerbubbleSoundComp;
};
