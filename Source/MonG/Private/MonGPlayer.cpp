// Fill out your copyright notice in the Description page of Project Settings.
#include <UMG/Public/Blueprint/UserWidget.h>
#include "MonGPlayer.h"
#include <../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h>
#include "EnhancedInputSubsystems.h"
#include <Engine/LocalPlayer.h>
#include <Camera/CameraComponent.h>
#include <MotionControllerComponent.h>
#include "Components/CapsuleComponent.h"
#include <Components/BoxComponent.h>
#include <NiagaraComponent.h>
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
#include "Marker.h"
#include "Postit.h"
#include "DustStrollSpawner.h"
#include "ScoreWidgetActor.h"
#include "ScoreWidget.h"
#include "PointWidget.h"
#include <HeadMountedDisplayFunctionLibrary.h>
#include <UMG/Public/Components/WidgetInteractionComponent.h>



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

	rightAim = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("rightAim"));
	rightAim->SetupAttachment(RootComponent);
	rightAim->SetTrackingMotionSource(FName("rightAim"));
	widgetInteractionComp = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("widgetInteractionComp"));
	widgetInteractionComp->SetupAttachment(rightAim);

	//ending위젯
	ending_UI = CreateDefaultSubobject<UEndingWidget>(TEXT("ending_UI"));
	endWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("endWidgetComp"));
	endWidgetComp->SetupAttachment(camera);
	endWidgetComp->SetWorldLocation(FVector(249, 2, -46));
	endWidgetComp->SetWorldRotation(FRotator(0.1, 540, 360));
	endWidgetComp->SetWorldScale3D(FVector((0.437500)));
}

// Called when the game starts or when spawned
void AMonGPlayer::BeginPlay()
{
	Super::BeginPlay();

	endWidgetComp->SetVisibility(false);
	playerController = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());
	actorStartWidget = Cast<AActorStartWidget>(UGameplayStatics::GetActorOfClass(GetWorld(), AActorStartWidget::StaticClass()));
	playWidget = Cast<UPlayWidget>(UGameplayStatics::GetActorOfClass(GetWorld(), UPlayWidget::StaticClass()));
	dustStrollSpawner = Cast<ADustStrollSpawner>(UGameplayStatics::GetActorOfClass(GetWorld(), ADustStrollSpawner::StaticClass()));


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
	right->OnComponentBeginOverlap.AddDynamic(this, &AMonGPlayer::RightOnOverlap);
	left->OnComponentBeginOverlap.AddDynamic(this, &AMonGPlayer::LeftOnOverlap);
	dust = Cast<ADust>(UGameplayStatics::GetActorOfClass(GetWorld(), ADust::StaticClass()));
	monGgm = Cast<AMonGGameModeBase>(UGameplayStatics::GetGameMode(this));

	/////////////////////////////
	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled() == false)
	{
		// Hand 을 테스트 할 수 있는 위치로 이동
		rightHand->SetRelativeLocation(FVector(20, 20, 50));
		rightAim->SetRelativeLocation(FVector(20, 20, 50));
		// 카메라의 Use Pawn Control Rotation 을 활성화
		camera->bUsePawnControlRotation = true;
	}
	// 만약 HMD 가 열결되어 있다면
	else
	{
		// -> 기본 트랙킹 offset 설정
		UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Eye);
	}
	
	if (widgetInteractionComp)
	{
		widgetInteractionComp->InteractionDistance = 1000.0f;
		widgetInteractionComp->bEnableHitTesting = true;
	}

}

// Called every frame
void AMonGPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	/*
	startPos = rightAim->GetComponentLocation();
	endPos = startPos + rightAim->GetForwardVector() * 100;
	FHitResult lineInfo;
	FCollisionQueryParams params;
	bool isLineInfo = GetWorld()->LineTraceSingleByChannel(lineInfo, startPos, endPos, ECC_GameTraceChannel17, params);
	params.AddIgnoredActor(this);

	if (isLineInfo == true)
	{
		PRINTTOScreen(FString::Printf(TEXT("WhiteBoard")));
		DrawDebugLine(GetWorld(), startPos, endPos, FColor::Red, false, -1, 0, -1);

	}

	*/
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
		inputSystem->BindAction(IA_LeftCleaning, ETriggerEvent::Started, this, &AMonGPlayer::LeftClean);
		inputSystem->BindAction(IA_RightCleaning, ETriggerEvent::Started, this, &AMonGPlayer::RightClean);
		inputSystem->BindAction(IA_LeftCleaning, ETriggerEvent::Completed, this, &AMonGPlayer::LeftStopClean);
		inputSystem->BindAction(IA_RightCleaning, ETriggerEvent::Completed, this, &AMonGPlayer::RightStopClean);
		inputSystem->BindAction(IA_LeftHold, ETriggerEvent::Started, this, &AMonGPlayer::LeftHold);
		inputSystem->BindAction(IA_LeftHold, ETriggerEvent::Completed, this, &AMonGPlayer::LeftPut);
		inputSystem->BindAction(IA_RightHold, ETriggerEvent::Started, this, &AMonGPlayer::RightHold);
		inputSystem->BindAction(IA_RightHold, ETriggerEvent::Completed, this, &AMonGPlayer::RightPut);
		inputSystem->BindAction(IA_Quit, ETriggerEvent::Started, this, &AMonGPlayer::PressUIBulletButten);
		inputSystem->BindAction(IA_RightA, ETriggerEvent::Started, this, &AMonGPlayer::PressRightBulletButten);
		inputSystem->BindAction(IA_Quit, ETriggerEvent::Completed, this, &AMonGPlayer::UIButten);
		inputSystem->BindAction(IA_RightA, ETriggerEvent::Completed, this, &AMonGPlayer::UIButten);
		inputSystem->BindAction(IA_RightDraw, ETriggerEvent::Triggered, this, &AMonGPlayer::RightDrawing);
		inputSystem->BindAction(IA_GameExit, ETriggerEvent::Triggered, this, &AMonGPlayer::MonGExit);
		
	}
}

void AMonGPlayer::Move(const FInputActionValue& Values)
{
	if (isGameStart == true)
	{
		FVector2D axis = Values.Get<FVector2D>();
		AddMovementInput(GetActorForwardVector(), axis.X);
		AddMovementInput(GetActorRightVector(), axis.Y);
	}
}

void AMonGPlayer::Look(const FInputActionValue& Values)
{
	FVector2D axis = Values.Get<FVector2D>();
	AddControllerYawInput(axis.X);
	AddControllerPitchInput(axis.Y);
}

void AMonGPlayer::LeftClean()
{
	if (isLeftCleanerHold == true)
	{
		if (isLeftHold == true)
		{

			if (cleaner != nullptr)
			{
				//PRINTTOScreen(FString::Printf(TEXT("leftCleeeeeeaning")));
				//마우스 클릭시 청소기 돌아가게
				isLeftClean = true;
				//청소효과
				AActor* cleanFX = GetWorld()->SpawnActor<ACleaningEffect>(cleaner->cleaningEffect, cleaner->cleanerHeadComp->GetComponentLocation(), cleaner->cleanerHeadComp->GetComponentRotation());
				cleanFX->AttachToComponent(cleaner->cleanerHeadComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("hand_lSocket"));
				APlayerController* PC = Cast<APlayerController>(GetController());
				//청소기 진동
				if (isLeftHold == true)
				{
					if (PC)
					{
						PC->PlayHapticEffect(HF_Clean, EControllerHand::Left);
					}
				}
			}
		}
	}
}

void AMonGPlayer::RightClean()
{
	pressed = true;

	if (isRightCleanerHold == true)
	{
		if (isRightHold == true)
		{

			if (cleaner != nullptr)
			{
				//마우스 클릭시 청소기 돌아가게
				isRightClean = true;
				//청소효과
				AActor* cleanFX = GetWorld()->SpawnActor<ACleaningEffect>(cleaner->cleaningEffect, cleaner->cleanerHeadComp->GetComponentLocation(), cleaner->cleanerHeadComp->GetComponentRotation());
				cleanFX->AttachToComponent(cleaner->cleanerHeadComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("hand_lSocket"));
				APlayerController* PC = Cast<APlayerController>(GetController());
				//청소기 진동
				if (isRightHold == true)
				{
					if (PC)
					{
						PC->PlayHapticEffect(HF_Clean, EControllerHand::Right);
					}
				}
			}
		}

	}
	else if(widgetInteractionComp && widgetInteractionComp->IsOverInteractableWidget())
	{
		if (pressed == true)
		{
			UE_LOG(LogTemp, Warning, TEXT("widgetpress"));
			widgetInteractionComp->PressPointerKey(EKeys::LeftMouseButton);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("widgetrelease"));
			widgetInteractionComp->ReleaseKey(EKeys::LeftMouseButton);
		}
	}
}


void AMonGPlayer::LeftStopClean()
{
	//마우스 클릭안하면 청소기 안돌아가게
	isLeftClean = false;

}

void AMonGPlayer::RightStopClean()
{
	isRightClean = false;
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
		isLeftCleanerHold = false;
		isRightCleanerHold = false;
		cleaner->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		cleaner->cleanerStick->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
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
		isLeftCleanerHold = false;
		isRightCleanerHold = false;
		cleaner->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		cleaner->cleanerStick->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
	if (marker != nullptr)
	{
		isRightHold = false;
		marker->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		marker->markerComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
}

void AMonGPlayer::PressUIBulletButten()
{
	//UE_LOG(LogTemp, Warning, TEXT("butten"));
	

	if (actorStartWidget != nullptr)
	{
		
		if (actorStartWidget != nullptr && actorStartWidget->isShowStartUI == true && isStartWidgetOff == false)
		{
		//////////	monGgm->Record
			monGgm->SaveScore();
			//UE_LOG(LogTemp, Warning, TEXT("startwidgetoff"));
			actorStartWidget->Destroy();
			isGameStart = true;
			isStartWidgetOff = true;
		}
	}
	
	if (isLeftCleanerHold == true)
	{
		//UE_LOG(LogTemp, Warning, TEXT("hold"));

		isRightCleanerHold = false;

		if (cleaner != nullptr)
		{
			cleaner->Shoot();
		}
	}

}

void AMonGPlayer::UIButten()
{

//	monGgm->isShowStartUI = false;
	if (cleaner != nullptr)
	{
		cleaner->isShoot = false;
	}
}

void AMonGPlayer::PressRightBulletButten()
{
	//PRINTTOScreen(FString::Printf(TEXT("right")));

	if (isRightCleanerHold == true)
	{
		//PRINTTOScreen(FString::Printf(TEXT("rightShoot")));

		isLeftCleanerHold = false;
		if (cleaner != nullptr)
		{
			cleaner->Shoot();
		}
	}
}

void AMonGPlayer::RightDrawing()
{
	if (marker != nullptr)
	{
		if (isRightHold == true)
		{
			marker->DrawingLine();
			//postit->Drawing();

		}
	}
}

void AMonGPlayer::GameEnding()
{
	if (isEndWidgetCompoff == false)
	{


		endWidgetComp->SetVisibility(true);
		dustStrollSpawner->Destroy();
		FTimerHandle endWidgetOffTimer;
		FTimerDelegate timerDelegate;
		timerDelegate.BindLambda([this]()->void {
			isGameStart = true;
		endWidgetComp->SetVisibility(false);
			});
		GetWorld()->GetTimerManager().SetTimer(endWidgetOffTimer, timerDelegate, 5.0f, false);
		isEndWidgetCompoff = true;
		////////////////////////////
		scoreWidgetActor = Cast<AScoreWidgetActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AScoreWidgetActor::StaticClass()));
		scoreWidgetActor->WidgetAppeared();

		auto scoreWidget = Cast<UScoreWidget>(scoreWidgetActor->scoreWidgetComp->GetWidget());
		scoreWidget->PrintCurrentScore();
		monGgm->RecordScore();
	}
}

//나가기
void AMonGPlayer::MonGExit()
{
	APlayerController* playerCon = GetWorld()->GetFirstPlayerController();
	UKismetSystemLibrary::QuitGame(GetWorld(), playerCon, EQuitPreference::Quit, true);
}

void AMonGPlayer::RightOnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//PRINTTOScreen(FString::Printf(TEXT("overllap")));

	//allObject = Cast<AAllObject>(OtherActor);
	cleaner = Cast<ACleaner>(OtherActor);
	marker = Cast<AMarker>(OtherActor);
	if (cleaner != nullptr)
	{
		if (isRightHold == true)
		{
			isRightCleanerHold = true;
			isLeftCleanerHold = false;
			//PRINTTOScreen(FString::Printf(TEXT("Rightholddddddd")));
			cleaner->cleanerStick->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			cleaner->AttachToComponent(rightHand, FAttachmentTransformRules::KeepWorldTransform);
		}
	}
	if (marker != nullptr)
	{
		//PRINTTOScreen(FString::Printf(TEXT("Rightholddddddd")));

		if (isRightHold == true)
		{

			marker->markerComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			marker->AttachToComponent(rightHand, FAttachmentTransformRules::KeepWorldTransform);
		}
	}
}

void AMonGPlayer::LeftOnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	//allObject = Cast<AAllObject>(OtherActor);
	cleaner = Cast<ACleaner>(OtherActor);
	if (cleaner != nullptr)
	{
		if (isLeftHold == true)
		{
			isLeftCleanerHold = true;
			isRightCleanerHold = false;
			//PRINTTOScreen(FString::Printf(TEXT("left")));
			cleaner->cleanerStick->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			cleaner->AttachToComponent(rightHand, FAttachmentTransformRules::KeepWorldTransform,FName("cleanerSocket"));

		}
	}

}


