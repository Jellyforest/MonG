// Fill out your copyright notice in the Description page of Project Settings.
#include <UMG/Public/Blueprint/UserWidget.h>
#include "MonGPlayer.h"
#include <../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h>
#include "EnhancedInputSubsystems.h"
#include <Engine/LocalPlayer.h>
#include <Camera/CameraComponent.h>
#include <MotionControllerComponent.h>
#include "Components/CapsuleComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include "Dust.h"
#include "PlayWidget.h"
#include "Components/SphereComponent.h"
#include <Kismet/GameplayStatics.h>
#include "Components/TextBlock.h"
#include <UMG/Public/Components/WidgetComponent.h>
#include <Components/ArrowComponent.h>
#include "CleaningEffect.h"
#include "Haptics/HapticFeedbackEffect_Curve.h"
#include "MonGGameModeBase.h"
#include "Cleaner.h"

#define PRINTTOScreen(msg) GEngine->AddOnScreenDebugMessage(0, 1, FColor::Blue, msg)
// Sets default values
AMonGPlayer::AMonGPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//ī�޶�
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("camera"));
	camera->SetupAttachment(RootComponent);
	camera->bUsePawnControlRotation = false;

	//�����¼���
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("PlayerPreset"));
	
	//�����Ʈ�ѷ�
	rightHand = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("rightHand"));
	rightHand->SetupAttachment(RootComponent);
	rightHand->SetTrackingMotionSource(FName("Right"));
	rightHandComp = CreateDefaultSubobject<USphereComponent>(TEXT("rightHandComp"));
	rightHandComp->SetupAttachment(rightHand);
	leftHand = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("leftHand"));
	leftHand->SetupAttachment(RootComponent);
	leftHand->SetTrackingMotionSource(FName("Left"));
	leftHandComp = CreateDefaultSubobject<USphereComponent>(TEXT("leftHandComp"));
	leftHandComp->SetupAttachment(leftHand);

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
	cleanerHead = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("cleanerHead"));
	cleanerHead->SetupAttachment(rightHand);
	cleanerHeadComp = CreateDefaultSubobject<USphereComponent>(TEXT("CleanerHeadComp"));
	cleanerHeadComp->SetupAttachment(cleanerHead);

	
	/////û�ұ� ������
	rightHandComp->SetCollisionProfileName(TEXT("PlayerHandPreset"));
	rightHand->SetCollisionProfileName(TEXT("PlayerHandPreset"));
	leftHandComp->SetCollisionProfileName(TEXT("PlayerHandPreset"));
	//////cleanerComp->SetCollisionProfileName(TEXT("CleanerPreset"));

	//�ð�, ���� ����
	play_UI = CreateDefaultSubobject<UPlayWidget>(TEXT("play_UI"));
	widgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("widgetComp"));
	widgetComp->SetupAttachment(camera);
	widgetComp->SetWorldLocation(FVector(249, 2, -46));
	widgetComp->SetWorldRotation(FRotator(360, 540, 1));
	widgetComp->SetWorldScale3D(FVector(0.4, 0.4, 0.4));
}

// Called when the game starts or when spawned
void AMonGPlayer::BeginPlay()
{
	Super::BeginPlay();

	playerController = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());
	play_UI = CreateWidget<UPlayWidget>(GetWorld(), playWidget);

	if (playerController)
	{
		auto localPlayer = playerController->GetLocalPlayer();
		auto subSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(localPlayer);
		if (subSystem)
		{
			subSystem->AddMappingContext(IMC_MonGInput, 0);
			subSystem->AddMappingContext(IMC_Hand, 0);
		}
	}

	rightHand->OnComponentBeginOverlap.AddDynamic(this, &AMonGPlayer::OnOverlap);
	leftHandComp->OnComponentBeginOverlap.AddDynamic(this, &AMonGPlayer::OnOverlap);
	//�ð�, ->OnComponentBeginOverlap.AddDynamic(this, &AMonGPlayer::OnOverlap);

	dust = Cast<ADust>(UGameplayStatics::GetActorOfClass(GetWorld(), ADust::StaticClass()));
	
	//���� ����ٲٱ�
	if (dust)
	{
		monGDirection = cleanerHead->GetComponentLocation()-dust->GetActorLocation();
		monGDirection.Normalize();
	}
	//�ð� ����
	play_UI->AddToViewport();
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
		inputSystem->BindAction(IA_Cleaning, ETriggerEvent::Completed, this, &AMonGPlayer::StopClean);
		inputSystem->BindAction(IA_MonGGrap, ETriggerEvent::Started, this, &AMonGPlayer::Hold);
		inputSystem->BindAction(IA_MonGGrap, ETriggerEvent::Completed, this, &AMonGPlayer::StopHold);
	}

}

void AMonGPlayer::Move(const FInputActionValue& Values)
{
	FVector2D axis = Values.Get<FVector2D>();
	AddMovementInput(GetActorForwardVector(), axis.X);
	AddMovementInput(GetActorRightVector(), axis.Y);

}

void AMonGPlayer::Look(const FInputActionValue& Values)
{
	FVector2D axis = Values.Get<FVector2D>();
	AddControllerYawInput(axis.X);
	AddControllerPitchInput(axis.Y);

}

void AMonGPlayer::Clean()
{
	//���콺 Ŭ���� û�ұ� ���ư���
	isClean = true;

	/*
	//û��ȿ��
	AActor* cleanFX = GetWorld()->SpawnActor<ACleaningEffect>(cleaningEffect, cleanerHeadComp->GetComponentLocation(), cleanerHeadComp->GetComponentRotation());
	cleanFX->AttachToComponent(cleanerHeadComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("hand_lSocket"));
	*/
	
	//û�ұ� ����
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		PC->PlayHapticEffect(HF_Clean, EControllerHand::Right);
	}
	
}

void AMonGPlayer::StopClean()
{
	//���콺 Ŭ�����ϸ� û�ұ� �ȵ��ư���
	isClean = false;
}

void AMonGPlayer::Hold()
{
	isHold = true;

}

void AMonGPlayer::StopHold()
{
	isHold = false;

}

void AMonGPlayer::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	cleaner = Cast<ACleaner>(OtherActor);
	PRINTTOScreen(FString::Printf(TEXT("Overlap")));


	if (isHold == true)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hold==true"));
		cleaner->playerOverlapComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		cleaner->AttachToComponent(rightHand, FAttachmentTransformRules::KeepWorldTransform);
		cleaner->AttachToComponent(leftHand, FAttachmentTransformRules::KeepWorldTransform);

	}

	/*
	dust=Cast<ADust>(OtherActor);
	if (isClean == true)
	{
		


		dust->moveSpeed = 5;
		dust->dustComp->SetSimulatePhysics(false);
		dust->dustComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		dust->AttachToComponent(cleanerHead, FAttachmentTransformRules::KeepWorldTransform);
		//////////����
		AGameModeBase* gm = UGameplayStatics::GetGameMode(this);
		AMonGGameModeBase* monGgm = Cast<AMonGGameModeBase>(gm);
		monGgm->AddScore(dust->point);
		dust->getPoint = true;

		FTimerHandle destroyTimer;
		FTimerDelegate timerDelegate;
		timerDelegate.BindLambda([this]()->void {	
		if (dust != nullptr)
		{
			dust->Destroy();
		}
		});
		GetWorld()->GetTimerManager().SetTimer(destroyTimer, timerDelegate, 0.5f, false);
	}
	*/
}
//Ȯ��
