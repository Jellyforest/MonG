// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PlayWidget.h"
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
	class UInputMappingContext* IMC_Hand;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_MonGMove;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_MonGMouse;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_LeftCleaning;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_RightCleaning;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_LeftHold;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_RightHold;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Input")
	class UInputAction* IA_Quit;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_RightA;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_Draw;
	//나가기 키
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_GameExit;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class APlayerController* playerController;



	//카메라
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* camera;


	//컨트롤러
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="MotionController")
	class UMotionControllerComponent* rightHand;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="MotionController")
	class UBoxComponent* right;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,Category="MotionController")
	class UMotionControllerComponent* leftHand;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,Category="MotionController")
	class UBoxComponent* left;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,Category="MotionController")
	class USkeletalMeshComponent* rightMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,Category="MotionController")
	class USkeletalMeshComponent* leftMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,Category="MotionController")
	class UInputMappingContext* IMC_Hands;
	// 집게손가락 모션컨트롤러
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MotionController", meta = (AllowPrivateAccess = true))
	class UMotionControllerComponent* rightAim;
	//위젯상호작용
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="WidgetController")
	class UWidgetInteractionComponent* widgetInteractionComp;


	//청소진동
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CleanerSettings")
	class UHapticFeedbackEffect_Curve* HF_Clean;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CleanerSettings")
	class ACleaner* cleaner;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class AAllObject* allObject; 

	//ending위젯
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EndingWidget")
	TSubclassOf <class UEndingWidget> endingWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EndingWidget")
	class UEndingWidget* ending_UI;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EndingWidget")
	class UWidgetComponent* endWidgetComp;
	
	//게임플레위젯
	UPROPERTY()
	class UPlayWidget* playWidget;
	UPROPERTY()
	class APlayWidgetActor* playWidgetActor;

	//시작위젯
	UPROPERTY()
	class AActorStartWidget* actorStartWidget;
	
	//점수 위젯
	UPROPERTY()
	class AScoreWidgetActor* scoreWidgetActor;
	UPROPERTY()
	class UScoreWidget* scoreWidget;
	//마커펜
	UPROPERTY()
	class AMarker* marker;
	//키보드
	UPROPERTY()
	class AKeyBoard* keyboard;
	//포스트잇
	UPROPERTY()
	class APostit* postit;
	//먼지보스
	UPROPERTY()
	class ADustStrollSpawner* dustStrollSpawner;	
	//게임모드
	UPROPERTY()
	class AMonGGameModeBase* monGgm;
	//Line
	UPROPERTY()
	FVector endPos;
	UPROPERTY()
	FVector startPos;


	//동작함수
	void Move(const FInputActionValue& Values);
	void Look(const FInputActionValue& Values);
	void LeftClean();
	void RightClean();
	void LeftStopClean();
	void RightStopClean();
	void LeftHold();
	void LeftPut();
	void RightHold();
	void RightPut();
	UFUNCTION(BluePrintCallable)
	void PressUIBulletButten();
	void UIButten();
	void PressRightBulletButten();
	//그림그리기
	void RightDrawing();
	void RightStopDrawing();
	//ending위젯 함수
	void GameEnding();
	//나가기
	void MonGExit();

	//청소기 
	UFUNCTION()
	void RightOnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void LeftOnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
            
	//먼지
	UPROPERTY()
	class ADust* dust;

	bool isLeftClean = false;
	bool isRightClean = false;
	bool isLeftHold = false;
	bool isRightHold = false;
	bool onButten = false;
	bool isGameStart = false;
	bool isRightCleanerHold = false;
	bool isLeftCleanerHold =false;
	bool isEndWidgetCompoff = false;
	bool isStartWidgetOff = false;
	bool isStartWidgetOffAndShoot = true;


	//위젯상호작용 키
	bool pressed = false;
};


