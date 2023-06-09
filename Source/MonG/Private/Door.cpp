// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Components/TimelineComponent.h>

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	doorComp = CreateDefaultSubobject<UBoxComponent>(TEXT("doorComp"));
	SetRootComponent(RootComponent);
	doorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("doorMesh"));
	doorMesh->SetupAttachment(doorComp);

	doorTimeLine = CreateDefaultSubobject<UTimelineComponent>(TEXT("doorTimeLine"));

}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();

	doorComp->OnComponentBeginOverlap.AddDynamic(this, &ADoor::InDoorComp);
	doorComp->OnComponentEndOverlap.AddDynamic(this, &ADoor::OutDoorComp);
	if (doorFloat)
	{
		FOnTimelineFloat TimelineCallback;
		FOnTimelineEventStatic TimelineFinishedCallback;

		TimelineCallback.BindUFunction(this, FName("ControlDoor"));
		TimelineFinishedCallback.BindUFunction(this, FName{ TEXT("SetState") });
		updateFloat.AddInterpFloat(doorFloat, TimelineCallback);
		updateFloat.SetTimelineFinishedFunc(TimelineFinishedCallback);
	}
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoor::UpdateTimeLine(float output)
{
	// 타임라인 커브(Timeline Curve)의 출력을 바탕으로 문의 새 상대적 위치 설정 및 구성
	FRotator doorNewRotation = FRotator(-2600, 0, 0);
	doorMesh->SetRelativeRotation(doorNewRotation);
}

void ADoor::InDoorComp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("in"));
	FVector startPoint = GetActorLocation();
	FVector endPoint = startPoint + FVector(0, -200, 0);
	doorTimeLine->PlayFromStart();
}

void ADoor::OutDoorComp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("out"));

	doorTimeLine->Reverse();
}

//확인
