// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KeyBoard.generated.h"

UCLASS()
class MONG_API AKeyBoard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKeyBoard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="KeyBoardSettings")
	class UStaticMeshComponent* keyboardMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="KeyBoardSettings")
	class UBoxComponent* aComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="KeyBoardSettings")
	class UBoxComponent* bComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="KeyBoardSettings")
	class UWidgetComponent* keyboardWidgetComp;
	

};
