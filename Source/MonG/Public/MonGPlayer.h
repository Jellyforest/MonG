
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
	class UInputAction* IA_MonGMove;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_MonGMouse;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_Cleaning;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class APlayerController* playerController;
	

	//ī�޶�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* camera;


	//��Ʈ�ѷ�
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="MotionController")
	class UMotionControllerComponent* rightHand;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,Category="MotionController")
	class UMotionControllerComponent* leftHand;
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
	//û��FX
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CleanerSettings")
	TSubclassOf <class ACleaningEffect> cleaningEffect;

	//�����Լ�
	void Move(const FInputActionValue& Values);
	void Look(const FInputActionValue& Values);
	void Clean();
	void StopClean();





	//û�ұ� 
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//����
	class ADust* dust;
	FVector monGDirection;
	float moveSpeed = 5;
	float deltaTime;
	float currentTime;
	float cleaningTime = 1;
	float cleaningTime1 = 4;

	bool isClean = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayTime")
	TSubclassOf <class UPlayWidget> playWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="PlayTime")
	class UPlayWidget* play_UI;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="PlayTime")
	class UWidgetComponent* widgetComp;
	



};
//Ȯ��

