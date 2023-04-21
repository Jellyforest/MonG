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
#include "Components/SphereComponent.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AMonGPlayer::AMonGPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//ī�޶�
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("camera"));
	camera->SetupAttachment(RootComponent);
	camera->bUsePawnControlRotation = true;
	//�����¼���
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("PlayerPreset"));
	
	//�����Ʈ�ѷ�
	rightHand = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("rightHand"));
	rightHand->SetupAttachment(RootComponent);
	rightHand->SetTrackingMotionSource(FName("Right"));
	leftHand = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("leftHand"));
	leftHand->SetupAttachment(RootComponent);
	leftHand->SetTrackingMotionSource(FName("Left"));
	//�����Ʈ�ѷ� ������ Mesh
	rightMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("rightMesh"));
	rightMesh->SetupAttachment(rightHand);
	ConstructorHelpers::FObjectFinder<USkeletalMesh>tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/MannequinsXR/Meshes/SKM_QuinnXR_right.SKM_QuinnXR_right'"));
		if (tempMesh.Succeeded())
		{
			rightMesh->SetSkeletalMesh(tempMesh.Object);
			rightMesh->SetRelativeLocation(FVector(-2.9f, 3.5f, 4.5f));
			rightMesh->SetRelativeRotation(FRotator(25, 0, 90));
		}
	//�����Ʈ�ѷ� �޼� Mesh
	leftMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("leftMesh"));
	leftMesh->SetupAttachment(leftHand);
	ConstructorHelpers::FObjectFinder<USkeletalMesh>tempMesh2(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/MannequinsXR/Meshes/SKM_QuinnXR_left.SKM_QuinnXR_left'"));
	if (tempMesh2.Succeeded())
	{
		leftMesh->SetSkeletalMesh(tempMesh2.Object);
		leftMesh->SetRelativeLocation(FVector(-2.9f, -3.5f, 4.5f));
		leftMesh->SetRelativeRotation(FRotator(-25, -180, 90));
	}
	
	//û�ұ� ����
	cleanerComp = CreateDefaultSubobject<UBoxComponent>(TEXT("cleanerComp"));
	cleanerComp->SetupAttachment(rightHand);
	cleanerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("cleanerMesh"));
	cleanerMesh->SetupAttachment(cleanerComp);

	//û�ұ� ������
	cleanerComp->SetCollisionProfileName(TEXT("CleanerPreset"));
	cleanerHead=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("cleanerHead"));
	cleanerHead->SetupAttachment(rightHand);
	cleanerHeadComp = CreateDefaultSubobject<USphereComponent>(TEXT("CleanerHeadComp"));
	cleanerHeadComp->SetupAttachment(cleanerHead);
	
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

	cleanerComp->OnComponentBeginOverlap.AddDynamic(this, &AMonGPlayer::OnOverlap);

	dust = Cast<ADust>(UGameplayStatics::GetActorOfClass(GetWorld(), ADust::StaticClass()));
	
	//���� ����ٲٱ�
	if (dust)
	{
		monGDirection = cleanerHead->GetComponentLocation()-dust->GetActorLocation();
		monGDirection.Normalize();
	}
	
	Timer();
}

// Called every frame
void AMonGPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	//UE_LOG(LogTemp, Warning, TEXT("%d"), timer);
	UE_LOG(LogTemp, Warning, TEXT("%d,%d,%d"), minute,timer,second);
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
		inputSystem->BindAction(IA_Cleaning, ETriggerEvent::Completed, this, &AMonGPlayer::StopClean);
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
	//���콺 Ŭ���� �������ǰ�
	isClean = true;

}

void AMonGPlayer::StopClean()
{
	isClean = false;

}

void AMonGPlayer::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	dust=Cast<ADust>(OtherActor);
	if (isClean == true)
	{
	dust->moveSpeed = 5;
	dust->dustComp->SetSimulatePhysics(false);
	dust->dustComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	dust->AttachToComponent(cleanerHead, FAttachmentTransformRules::KeepWorldTransform);

	FTimerHandle destroyTimer;
	FTimerDelegate timerDelegate;
	timerDelegate.BindLambda([this]()->void {	
		if (dust != nullptr)
		{
			dust->Destroy();

		}
	});
	GetWorld()->GetTimerManager().SetTimer(destroyTimer, timerDelegate, 1.5f, false);
	}
	
}





void AMonGPlayer::Timer()
{
	FTimerHandle countTime;
	FTimerDelegate timerDelegate;
	timerDelegate.BindLambda([this]()->void {
		timer -= 1; minute = timer / 60; second = timer % 60;
	 });
	GetWorld()->GetTimerManager().SetTimer(countTime, timerDelegate, 1, true);
}
/*
timer--;
UE_LOG(LogTemp, Warning, TEXT("%f"), timer);
	float time = (300-timer) / 60;

*/