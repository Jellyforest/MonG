// Fill out your copyright notice in the Description page of Project Settings.


#include "MonGPlayer.h"
#include <../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h>
#include "EnhancedInputSubsystems.h"
#include <Engine/LocalPlayer.h>
#include <Camera/CameraComponent.h>

// Sets default values
AMonGPlayer::AMonGPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	


	//Ä«¸Þ¶ó
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("camera"));

}

// Called when the game starts or when spawned
void AMonGPlayer::BeginPlay()
{
	Super::BeginPlay();

	playerController = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());

	if (playerController)
	{
		auto localPlayer = playerController->GetLocalPlayer();
		auto subSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(localPlayer);
		if (subSystem)
		{
			subSystem->AddMappingContext(IMC_MonGInput, 0);
		}
	}
}

// Called every frame
void AMonGPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMonGPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* inputSystem = Cast <UEnhancedInputComponent>(PlayerInputComponent);
	if (inputSystem)
	{
		inputSystem->BindAction(IA_MonGMove, ETriggerEvent::Triggered, this, &AMonGPlayer::Move);
	}

}

void AMonGPlayer::Move(const FInputActionValue& Values)
{
	UE_LOG(LogTemp, Warning, TEXT("mmmoveee"));
	FVector2D axis = Values.Get<FVector2D>();
	AddMovementInput(FVector(1, 0, 0), axis.X);
	AddMovementInput(FVector(0, 1, 0), axis.Y);

}

