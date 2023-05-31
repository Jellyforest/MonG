// Fill out your copyright notice in the Description page of Project Settings.

#include "Marker.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Components/DecalComponent.h>
#include <Kismet/GameplayStatics.h>
#include "Postit.h"

#define PRINTTOScreen(msg) GEngine->AddOnScreenDebugMessage(0, 1, FColor::Blue, msg)

// Sets default values
AMarker::AMarker()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	markerComp = CreateDefaultSubobject<UBoxComponent>(TEXT("markerComp"));
	SetRootComponent(RootComponent);
	markerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("markerMesh"));
	markerMesh->SetupAttachment(markerComp);
	markerLead = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("markerLead"));
	markerLead->SetupAttachment(markerComp);
	markerComp->SetCollisionProfileName(TEXT("CleanerStickPreset"));
	//M_Marker = CreateDefaultSubobject<UMaterialInterface>(TEXT("M_Marker"));
	ConstructorHelpers::FObjectFinder<UMaterialInterface>tempMat(TEXT("/Script/Engine.Material'/Game/JY/Blueprints/M_Marker.M_Marker'"));
	if (tempMat.Succeeded())
	{
		M_Marker = tempMat.Object;
	}

}

// Called when the game starts or when spawned
void AMarker::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void AMarker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMarker::DrawingLine()
{
	FVector startPos = markerLead->GetComponentLocation();
	FVector endPos = startPos + markerLead->GetForwardVector() * 1;
	FHitResult drawInfo;
	FCollisionQueryParams params;
	//params.AddIgnoredActor(this);
	FVector NewSize = FVector(300);
	FRotator NewRotator;
	bool isdraw = GetWorld()->LineTraceSingleByChannel(drawInfo, startPos, endPos, ECC_GameTraceChannel10, params);
	if (isdraw && M_Marker)
	{
		PRINTTOScreen(FString::Printf(TEXT("Overlap")));
		postit = Cast<APostit>(drawInfo.GetActor());
		if (postit)
		{
			DrawDebugLine(GetWorld(), startPos, endPos, FColor::Red, false, -1, 0, -1);
			RangeDecal = UGameplayStatics::SpawnDecalAtLocation(this, M_Marker, NewSize, startPos, NewRotator, 0.0f);
			RangeDecal->SetRelativeRotation(NewRotator);
			RangeDecal->SetRelativeScale3D(FVector(0.05f));
			//SetFadeOut(0.0f, 1.0f);

		}
	}


}


