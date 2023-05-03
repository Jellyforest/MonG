// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "Door.generated.h"

UCLASS()
class MONG_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere,Category="Door Settings")
	class UBoxComponent* doorComp;

	UPROPERTY(EditAnywhere,Category="Door Settings")
	class UStaticMeshComponent* doorMesh;

	UPROPERTY(EditAnywhere,Category="Door Settings")
	class UTimelineComponent* doorTimeLine;

	// 커브 에셋을 보관하는 변수
	UPROPERTY(EditAnywhere,Category="Door Settings")
	class UCurveFloat* doorFloat;

	//업데이트 트랙 이벤트를 처리할 플로트 트랙 시그니처
	FOnTimelineFloat updateFloat;

	//타임라인 그래프에 따라 문의 상대적 위치를 업데이트하는 함수
	UFUNCTION()
	void UpdateTimeLine(float output);

	UFUNCTION()
	void InDoorComp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OutDoorComp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
