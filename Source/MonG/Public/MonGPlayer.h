
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
	class UInputAction* IA_Cleaning;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_LeftHold;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_RightHold;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_Quit;
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

	//û�ұ�
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,Category="CleanerSettings")
	class UStaticMeshComponent* cleanerMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,Category="CleanerSettings")
	class UBoxComponent* cleanerComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,Category="CleanerSettings")
	class UStaticMeshComponent* cleanerHead;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,Category="CleanerSettings")
	class USphereComponent* cleanerHeadComp;
	//û������
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CleanerSettings")
	class UHapticFeedbackEffect_Curve* HF_Clean;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CleanerSettings")
	class ACleaner* cleaner;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class AAllObject* allObject; 

	//�ð�����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayTime")
	TSubclassOf <class UPlayWidget> playWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="PlayTime")
	class UPlayWidget* play_UI;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="PlayTime")
	class UWidgetComponent* playWidgetComp;
	//��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StartWidget")
	TSubclassOf <class UStartWidget> startWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StartWidget")
	class UStartWidget* start_UI;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StartWidget")
	class UWidgetComponent* startWidgetComp;


	

	//�����Լ�
	void Move(const FInputActionValue& Values);
	void Look(const FInputActionValue& Values);
	void Clean();
	void StopClean();
	void LeftHold();
	void LeftPut();
	void RightHold();
	void RightPut();
	void PressUIButten();
	void UIButten();




	//û�ұ� 
	UFUNCTION()
	void RightOnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void LeftOnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
            
	//����
	UPROPERTY()
	class ADust* dust;
	FVector monGDirection;
	float moveSpeed = 5;
	float deltaTime;
	float currentTime;
	float cleaningTime = 1;
	float cleaningTime1 = 4;

	bool isClean = false;
	bool isLeftHold = false;
	bool isRightHold = false;
	bool onButten = false;
	



};
//Ȯ��


