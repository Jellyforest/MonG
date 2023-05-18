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
#include "AllObject.h"
#include "StartWidget.h"
#include "EndingWidget.h"
#include <Kismet/KismetSystemLibrary.h>
#include "ActorStartWidget.h"


#define PRINTTOScreen(msg) GEngine->AddOnScreenDebugMessage(0, 1, FColor::Blue, msg)
// Sets default values
AMonGPlayer::AMonGPlayer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//카메라
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("camera"));
	camera->SetupAttachment(RootComponent);
	camera->bUsePawnControlRotation = false;
	camera->SetWorldLocation(FVector(0, 0, 50));

	//프리셋세팅
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("PlayerPreset"));

	//모션컨트롤러
	rightHand = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("rightHand"));
	rightHand->SetupAttachment(RootComponent);
	rightHand->SetTrackingMotionSource(FName("Right"));
	rightHand->SetWorldLocation(FVector(0, 0, 50));
	right = CreateDefaultSubobject<UBoxComponent>(TEXT("right"));
	right->SetupAttachment(rightHand);
	right->SetCollisionProfileName(TEXT("PlayerHandsPreset"));
	leftHand = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("leftHand"));
	leftHand->SetupAttachment(RootComponent);
	leftHand->SetTrackingMotionSource(FName("Left"));
	left = CreateDefaultSubobject<UBoxComponent>(TEXT("left"));
	left->SetupAttachment(leftHand);
	left->SetCollisionProfileName(TEXT("PlayerHandsPreset"));
	//모션컨트롤러 오른손 Mesh
	rightMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("rightMesh"));
	rightMesh->SetupAttachment(rightHand);
	ConstructorHelpers::FObjectFinder<USkeletalMesh>tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/MannequinsXR/Meshes/SKM_QuinnXR_right.SKM_QuinnXR_right'"));
	if (tempMesh.Succeeded())
	{
		rightMesh->SetSkeletalMesh(tempMesh.Object);
		rightMesh->SetRelativeLocation(FVector(-2.9f, 10.5f, 4.5f));
		rightMesh->SetRelativeRotation(FRotator(25, 0, 90));
	}
	//모션컨트롤러 왼손 Mesh
	leftMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("leftMesh"));
	leftMesh->SetupAttachment(leftHand);
	ConstructorHelpers::FObjectFinder<USkeletalMesh>tempMesh2(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/MannequinsXR/Meshes/SKM_QuinnXR_left.SKM_QuinnXR_left'"));
	if (tempMesh2.Succeeded())
	{
		leftMesh->SetSkeletalMesh(tempMesh2.Object);
		leftMesh->SetRelativeLocation(FVector(-2.9f, 0.5f, 4.5f));
		leftMesh->SetRelativeRotation(FRotator(-25, -180, 90)); 
	}

	//청소기 세팅

	cleanerComp = CreateDefaultSubobject<UBoxComponent>(TEXT("cleanerComp"));
	cleanerComp->SetupAttachment(rightHand);
	cleanerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("cleanerMesh"));
	cleanerMesh->SetupAttachment(cleanerComp);
	cleanerHead = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("cleanerHead"));
	cleanerHead->SetupAttachment(rightHand);
	cleanerHeadComp = CreateDefaultSubobject<USphereComponent>(TEXT("CleanerHeadComp"));
	cleanerHeadComp->SetupAttachment(cleanerHead);


	//청소기 프리셋
	//cleanerComp->SetCollisionProfileName(TEXT("CleanerPreset"));
	//시간, 점수 위젯
	play_UI = CreateDefaultSubobject<UPlayWidget>(TEXT("play_UI"));
	//play_UI = CreateWidget<UPlayWidget>(GetWorld(), playWidget);
	playWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("playWidgetComp"));
	playWidgetComp->SetupAttachment(camera);
	playWidgetComp->SetWorldLocation(FVector(249, 2, -46));
	playWidgetComp->SetWorldRotation(FRotator(0.1, 540, 360));
	playWidgetComp->SetWorldScale3D(FVector((0.437500)));

	
}

// Called when the game starts or when spawned
void AMonGPlayer::BeginPlay()
{
	Super::BeginPlay();

	playerController = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());
	actorStartWidget= Cast<AActorStartWidget>(UGameplayStatics::GetActorOfClass(GetWorld(), AActorStartWidget::StaticClass()));

	playWidgetComp->SetVisibility(false);


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

	//cleanerComp->OnComponentBeginOverlap.AddDynamic(this, &AMonGPlayer::OnOverlap);
	right->OnComponentBeginOverlap.AddDynamic(this, &AMonGPlayer::RightOnOverlap);
	left->OnComponentBeginOverlap.AddDynamic(this, &AMonGPlayer::LeftOnOverlap);
	dust = Cast<ADust>(UGameplayStatics::GetActorOfClass(GetWorld(), ADust::StaticClass()));

	//먼지 방향바꾸기
	if (dust)
	{
		monGDirection = cleanerHead->GetComponentLocation() - dust->GetActorLocation();
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
		inputSystem->BindAction(IA_Cleaning, ETriggerEvent::Completed, this, &AMonGPlayer::StopClean);
		inputSystem->BindAction(IA_LeftHold, ETriggerEvent::Started, this, &AMonGPlayer::LeftHold);
		inputSystem->BindAction(IA_LeftHold, ETriggerEvent::Completed, this, &AMonGPlayer::LeftPut);
		inputSystem->BindAction(IA_RightHold, ETriggerEvent::Started, this, &AMonGPlayer::RightHold);
		inputSystem->BindAction(IA_RightHold, ETriggerEvent::Completed, this, &AMonGPlayer::RightPut);
		inputSystem->BindAction(IA_Quit, ETriggerEvent::Started, this, &AMonGPlayer::PressUIButten);
		inputSystem->BindAction(IA_Quit, ETriggerEvent::Completed, this, &AMonGPlayer::UIButten);
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
	if (isLeftHold == true || isRightHold == true)
	{
		//마우스 클릭시 청소기 돌아가게
		isClean = true;
		//청소효과
		AActor* cleanFX = GetWorld()->SpawnActor<ACleaningEffect>(cleaner->cleaningEffect, cleaner->cleanerHeadComp->GetComponentLocation(), cleaner->cleanerHeadComp->GetComponentRotation());
		cleanFX->AttachToComponent(cleaner->cleanerHeadComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("hand_lSocket"));
		
		//청소기 진동
		APlayerController* PC = Cast<APlayerController>(GetController());
		if (PC)
		{
			PC->PlayHapticEffect(HF_Clean, EControllerHand::Right);
		}
	}
}

void AMonGPlayer::StopClean()
{
	//마우스 클릭안하면 청소기 안돌아가게
	isClean = false;
}

void AMonGPlayer::LeftHold()
{
	isLeftHold = true;
	onButten = true;


}


void AMonGPlayer::LeftPut()
{
	if (cleaner != nullptr)
	{
		if (isLeftHold == false)
		{
			return;
		}

		// 1. 잡지않은 상태로 전환
		isLeftHold = false;
		PRINTTOScreen(FString::Printf(TEXT("put")));
		cleaner->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		cleaner->cleanerStick->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		//cleaner->cleanerStick->SetSimulatePhysics(true);
		onButten = false;

	}
}

void AMonGPlayer::RightHold()
{
	isRightHold = true;
	onButten = true;

}

void AMonGPlayer::RightPut()
{
	if (cleaner != nullptr)
	{
		if (isRightHold == false)
		{
			return;
		}
		onButten = false;

		// 1. 잡지않은 상태로 전환
		isRightHold = false;
		//PRINTTOScreen(FString::Printf(TEXT("put")));
		cleaner->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		cleaner->cleanerStick->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		//cleaner->cleanerStick->SetSimulatePhysics(true);
	}
}

void AMonGPlayer::PressUIButten()
{

	AGameModeBase* gm = UGameplayStatics::GetGameMode(this);
	AMonGGameModeBase* monGgm = Cast<AMonGGameModeBase>(gm);
	if (actorStartWidget != nullptr||monGgm->ending_UI !=nullptr)
	{
		if (actorStartWidget->isShowStartUI == true)
		{
			PRINTTOScreen(FString::Printf(TEXT("PressbuttenUI")));
			//UGameplayStatics::SetGamePaused(GetWorld(), false);
			actorStartWidget->Destroy();
			playWidgetComp->SetVisibility(true);
			isGameStart = true;
			//monGgm->start_UI->widgetSwitcher->SetActiveWidgetIndex(0);
		}
		if (monGgm->isShowEndingUI == true)
		{
		//	UGameplayStatics::SetGamePaused(GetWorld(), false);
			monGgm->ending_UI->RemoveFromParent();
			APlayerController* playerCon = GetWorld()->GetFirstPlayerController();
			UKismetSystemLibrary::QuitGame(GetWorld(), playerCon, EQuitPreference::Quit, true);
		}

	}
}

void AMonGPlayer::UIButten()
{
	AGameModeBase* gm = UGameplayStatics::GetGameMode(this);
	AMonGGameModeBase* monGgm = Cast<AMonGGameModeBase>(gm);
	monGgm->isShowStartUI = false;
}

void AMonGPlayer::RightOnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	PRINTTOScreen(FString::Printf(TEXT("overllap")));

	allObject = Cast<AAllObject>(OtherActor);
	cleaner = Cast<ACleaner>(OtherActor);
	if (cleaner != nullptr)
	{
		if (isRightHold == true)
		{
			PRINTTOScreen(FString::Printf(TEXT("Rightholddddddd")));
			cleaner->cleanerStick->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			//cleaner->cleanerStick->SetSimulatePhysics(false);
			cleaner->AttachToComponent(rightHand, FAttachmentTransformRules::KeepWorldTransform);
			//cleaner->AttachToComponent(leftHand, FAttachmentTransformRules::KeepWorldTransform);
			//allObject->objectComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			//allObject->AttachToComponent(rightHand, FAttachmentTransformRules::KeepWorldTransform);
		}
	}
}

void AMonGPlayer::LeftOnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	allObject = Cast<AAllObject>(OtherActor);
	cleaner = Cast<ACleaner>(OtherActor);
	if (isLeftHold == true)
	{
		//PRINTTOScreen(FString::Printf(TEXT("left")));
		cleaner->cleanerStick->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		cleaner->AttachToComponent(leftHand, FAttachmentTransformRules::KeepWorldTransform);
		//allObject->objectComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		//allObject->AttachToComponent(rightHand, FAttachmentTransformRules::KeepWorldTransform);


	}

	
}



//확인