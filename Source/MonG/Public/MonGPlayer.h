
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

	//����
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
	class UInputAction* IA_RightDraw;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class APlayerController* playerController;



	//ī�޶�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* camera;


	//��Ʈ�ѷ�
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

	
	//û������
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CleanerSettings")
	class UHapticFeedbackEffect_Curve* HF_Clean;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CleanerSettings")
	class ACleaner* cleaner;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class AAllObject* allObject; 

	//ending����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EndingWidget")
	TSubclassOf <class UEndingWidget> endingWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EndingWidget")
	class UEndingWidget* ending_UI;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EndingWidget")
	class UWidgetComponent* endWidgetComp;
	
	//�����÷�����
	UPROPERTY()
	class UPlayWidget* playWidget;

	//��������
	UPROPERTY()
	class AActorStartWidget* actorStartWidget;

	//��Ŀ��
	UPROPERTY()
	class AMarker* marker;

	//����Ʈ��
	UPROPERTY()
	class APostit* postit;
	//
	UPROPERTY()
	class ADustStrollSpawner* dustStrollSpawner;	

	//�����Լ�
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
	//�׸��׸���
	void RightDrawing();
	
	//ending���� �Լ�
	void GameEnding();


	//û�ұ� 
	UFUNCTION()
	void RightOnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void LeftOnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
            
	//����
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

};


