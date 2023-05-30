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
	markerMat = CreateDefaultSubobject<UMaterial>(TEXT("markerMat"));


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
	FVector endPos = startPos + markerLead->GetForwardVector() * 10;
	FHitResult drawInfo;
	FCollisionQueryParams params;
	//params.AddIgnoredActor(this);
	FVector NewSize(10);
	FRotator NewRotator;
	bool isdraw = GetWorld()->LineTraceSingleByChannel(drawInfo, startPos, endPos, ECC_GameTraceChannel10, params);
	if (isdraw)
	{
		PRINTTOScreen(FString::Printf(TEXT("Overlap")));
		postit = Cast<APostit>(drawInfo.GetActor());
		if (postit)
		{
			DrawDebugLine(GetWorld(), startPos, endPos, FColor::Red, false, -1, 0, -1);
			RangeDecal = UGameplayStatics::SpawnDecalAtLocation(this, markerMat, NewSize, endPos, NewRotator, 0.0f);
			RangeDecal->SetRelativeRotation(NewRotator);
				//SetFadeOut(0.0f, 1.0f);

		}
	}


}



