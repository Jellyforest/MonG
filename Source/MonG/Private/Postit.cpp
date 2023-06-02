// Fill out your copyright notice in the Description page of Project Settings.


#include "Postit.h"
#include <Materials/MaterialInstance.h>
#include <Kismet/KismetRenderingLibrary.h>
#include <Engine/CanvasRenderTarget2D.h>
#include <Materials/MaterialInstanceDynamic.h>
#include <Kismet/GameplayStatics.h>
#include "Marker.h"
#include "Math/Vector.h"
#include <Kismet/KismetMaterialLibrary.h>

#define PRINTTOScreen(msg) GEngine->AddOnScreenDebugMessage(0, 1, FColor::Blue, msg)

// Sets default values
APostit::APostit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	markerInk = CreateDefaultSubobject<UMaterial>(TEXT("markerInk"));
	postitLander = CreateDefaultSubobject<UCanvasRenderTarget2D>(TEXT("postitLander"));
	//boardMarker = CreateDefaultSubobject<UMaterialInstanceDynamic>(TEXT("boardMarker"));
	//boardMarker = CreateDefaultSubobject<UMaterial>(TEXT("boardMarker"));
	//boardMarker->UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), markerInk );
	//UKismetMaterialLibrary::CreateDynamicMaterialInstance()
}

// Called when the game starts or when spawned
void APostit::BeginPlay()
{
	Super::BeginPlay();

	boardMarker = UMaterialInstanceDynamic::Create(markerInk, this);
	marker = Cast<AMarker>(UGameplayStatics::GetActorOfClass(GetWorld(), AMarker::StaticClass()));

	UKismetRenderingLibrary::ClearRenderTarget2D(GetWorld(), postitLander);

}

// Called every frame
void APostit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APostit::Drawing()
{
		//UE_LOG(LogTemp, Warning, TEXT("APostit :: Drawing"))
		PRINTTOScreen(FString::Printf(TEXT("Drawwwwwwwwwwwing")));
		//drawLocation = marker->endPos;
		if (marker != nullptr)
		{
			FVector2D _locationToDraw = marker->locationToDraw;
			FVector vecLocationToDraw(_locationToDraw, 0.1f); 
			FLinearColor lineLocationToDraw(vecLocationToDraw);
			boardMarker->SetVectorParameterValue(drawLocation, lineLocationToDraw);
			UKismetRenderingLibrary::DrawMaterialToRenderTarget(GetWorld(), postitLander, boardMarker);
		}
	
}

void APostit::DrawSize(float drawSize)
{
	boardMarker->SetScalarParameterValue(drawSizePram, drawSize);
}

