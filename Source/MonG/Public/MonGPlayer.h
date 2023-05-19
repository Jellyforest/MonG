
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
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_Quit;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_RightA;
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

	
	//청소진동
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CleanerSettings")
	class UHapticFeedbackEffect_Curve* HF_Clean;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CleanerSettings")
	class ACleaner* cleaner;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class AAllObject* allObject; 

	//시간위젯
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayTime")
	TSubclassOf <class UPlayWidget> playWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="PlayTime")
	class UPlayWidget* play_UI;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="PlayTime")
	class UWidgetComponent* playWidgetComp;
	
	//시작위젯
	UPROPERTY()
	class AActorStartWidget* actorStartWidget;


	//동작함수
	void Move(const FInputActionValue& Values);
	void Look(const FInputActionValue& Values);
	void LeftClean();
	void RightClean();
	void StopClean();
	void LeftHold();
	void LeftPut();
	void RightHold();
	void RightPut();
	void PressUIBulletButten();
	void UIButten();
	void PressRightBulletButten();



	//청소기 
	UFUNCTION()
	void RightOnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void LeftOnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
            
	//먼지
	UPROPERTY()
	class ADust* dust;

	bool isClean = false;
	bool isLeftHold = false;
	bool isRightHold = false;
	bool onButten = false;
	bool isGameStart = false;
	bool isRightCleanerHold = false;
	bool isLeftCleanerHold =false;
	


};
//확인


