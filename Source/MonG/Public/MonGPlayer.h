// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "MonGPlayer.generated.h"

UCLASS()
class MONG_API AMonGPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonGPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//동작
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* IMC_MonGInput;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_MonGMove;
	//카메라
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* camera;

	UPROPERTY()
	class APlayerController* playerController;

	UFUNCTION()
	void Move(const FInputActionValue& Values);
};
