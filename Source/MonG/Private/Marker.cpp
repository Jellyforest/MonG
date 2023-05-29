// Fill out your copyright notice in the Description page of Project Settings.


#include "Marker.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
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
	FVector endPos = startPos + markerLead->GetForwardVector() * 10000;
	FHitResult hitInfo;
	FCollisionQueryParams params;
	//params.AddIgnoredActor(this);
	bool ishit = GetWorld()->LineTraceSingleByChannel(hitInfo, startPos, endPos, ECC_GameTraceChannel10, params);
	if (ishit)
	{
		PRINTTOScreen(FString::Printf(TEXT("Overlap")));


		auto postIt = Cast<APostit>(hitInfo.GetActor());
		if (postIt)
		{
			DrawDebugLine(GetWorld(), startPos, endPos, FColor::Red, false, -1, 0, -1);

		}
	}
	//bool bHit = HitTest(startPos, endPos, hitInfo);
	//if (bHit && hitInfo.GetActor()
//	{

	//}

}

//bool AMarker::HitTest(FVector startPos, FVector endPos, FHitResult& hitInfo)
//{

//}

