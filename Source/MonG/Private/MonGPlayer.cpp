// Fill out your copyright notice in the Description page of Project Settings.


#include "MonGPlayer.h"
#include <../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h>
#include "EnhancedInputSubsystems.h"
#include <Engine/LocalPlayer.h>
#include <Camera/CameraComponent.h>
#include <MotionControllerComponent.h>
#include "Components/CapsuleComponent.h"
#include <GameFramework/Actor.h>
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include "Dust.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AMonGPlayer::AMonGPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//카메라
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("camera"));
	camera->SetupAttachment(RootComponent);
	camera->bUsePawnControlRotation = true;
	//프리셋세팅
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("PlayerPreset"));
	
	//모션컨트롤러
	rightHand = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("rightHand"));
	rightHand->SetupAttachment(RootComponent);
	rightHand->SetTrackingMotionSource(FName("Right"));
	leftHand = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("leftHand"));
	leftHand->SetupAttachment(RootComponent);
	leftHand->SetTrackingMotionSource(FName("Left"));
	//모션컨트롤러 오른손 Mesh
	rightMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("rightMesh"));
	rightMesh->SetupAttachment(rightHand);
	ConstructorHelpers::FObjectFinder<USkeletalMesh>tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/MannequinsXR/Meshes/SKM_QuinnXR_right.SKM_QuinnXR_right'"));
		if (tempMesh.Succeeded())
		{
			rightMesh->SetSkeletalMesh(tempMesh.Object);
			rightMesh->SetRelativeLocation(FVector(-2.9f, 3.5f, 4.5f));
			rightMesh->SetRelativeRotation(FRotator(25, 0, 90));
		}
	//모션컨트롤러 왼손 Mesh
	leftMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("leftMesh"));
	leftMesh->SetupAttachment(leftHand);
	ConstructorHelpers::FObjectFinder<USkeletalMesh>tempMesh2(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/MannequinsXR/Meshes/SKM_QuinnXR_left.SKM_QuinnXR_left'"));
	if (tempMesh2.Succeeded())
	{
		leftMesh->SetSkeletalMesh(tempMesh2.Object);
		leftMesh->SetRelativeLocation(FVector(-2.9f, -3.5f, 4.5f));
		leftMesh->SetRelativeRotation(FRotator(-25, -180, 90));
	}
	
	//청소기 세팅
	cleannerComp = CreateDefaultSubobject<UBoxComponent>(TEXT("cleannerComp"));
	cleannerComp->SetupAttachment(rightHand);
	cleannerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("cleannerMesh"));
	cleannerMesh->SetupAttachment(cleannerComp);

	//청소기 프리셋
	cleannerComp->SetCollisionProfileName(TEXT("CleannerPreset"));

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
			subSystem->AddMappingContext(IMC_Hands, 0);
		}
	}

	cleannerComp->OnComponentBeginOverlap.AddDynamic(this, &AMonGPlayer::OnOverlap);

	dust = Cast<ADust>(UGameplayStatics::GetActorOfClass(GetWorld(), ADust::StaticClass()));
	if (dust)
	{
		monGDirection = cleannerMesh->GetComponentLocation()-dust->GetActorLocation();
		monGDirection.Normalize();
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
		inputSystem->BindAction(IA_MonGMouse, ETriggerEvent::Triggered, this, &AMonGPlayer::Look);
		inputSystem->BindAction(IA_Cleaning, ETriggerEvent::Started, this, &AMonGPlayer::Clean);
	}

}

void AMonGPlayer::Move(const FInputActionValue& Values)
{
	FVector2D axis = Values.Get<FVector2D>();
	AddMovementInput(FVector(1, 0, 0), axis.X);
	AddMovementInput(FVector(0, 1, 0), axis.Y);

}

void AMonGPlayer::Look(const FInputActionValue& Values)
{
	FVector2D axis = Values.Get<FVector2D>();
	AddControllerYawInput(axis.X);
	AddControllerPitchInput(axis.Y);

}

void AMonGPlayer::Clean()
{
	//Lintrace 시작위치
	FVector startPoint = cleannerMesh->GetComponentLocation();
	//Lintrace 종료위치 
	FVector endPoint = cleannerMesh->GetComponentLocation() + cleannerMesh->GetForwardVector() * 500;
	//Linetrace의 충돌 정보를 담을 변수
	FHitResult hitInfo;

}

void AMonGPlayer::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//inClenner = true;
	//UE_LOG(LogTemp, Warning, TEXT("overrrrrrrrrrlap"));
	//UE_LOG(LogTemp, Warning, TEXT("overrrrrrrrrrlap - %s"), *OtherActor->GetName());
	dust=Cast<ADust>(OtherActor);
	if (dust != nullptr) 
	{
		//UE_LOG(LogTemp, Warning, TEXT("In"));
		inClenner = true;
		deltaTime = GetWorld()->DeltaTimeSeconds;
		currentTime += GetWorld()->DeltaTimeSeconds;
		if (currentTime < cleaningTime && currentTime < cleaningTime1)
		{
			UE_LOG(LogTemp, Warning, TEXT("cleanintimeYat"));
			dust->moveSpeed = 0;

		}
		if (currentTime > cleaningTime1)
		{
			UE_LOG(LogTemp, Warning, TEXT("cleaninTime"));
			dust->SetActorLocation(GetActorLocation() + monGDirection * moveSpeed * deltaTime);
			//currentTime = 0;
		}
		
	}
	//if (dust)
	//{
	////	
	//}
}

