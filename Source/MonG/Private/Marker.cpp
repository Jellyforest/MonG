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
	//¸¶Ä¿ »ö±ò
	//SetVectorParameterValueOnMaterials(FName("doorStateColor"), FVector4(0.505f, 0.015f, 0.00974f, 1));
	ConstructorHelpers::FObjectFinder<UMaterialInstance> penColor(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/JY/Blueprints/M_Marker_Inst.M_Marker_Inst'"));
	if (penColor.Succeeded())
	{
		markerLead->SetMaterial(0, penColor.Object);

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
	APostit* postit = Cast<APostit>(UGameplayStatics::GetActorOfClass(GetWorld(), APostit::StaticClass()));
	if (postit)
	{
		startPos = markerLead->GetComponentLocation();
		endPos = startPos + markerLead->GetForwardVector() * 1;
		FHitResult drawInfo;
		FCollisionQueryParams params;
		//FVector2D locationToDraw;
		//UGameplayStatics::FindCollisionUV(drawInfo, 0, locationToDraw);
		//params.AddIgnoredActor(this);
		//FVector NewSize = FVector(500);
		//FRotator NewRotator;
		//bool isdraw = GetWorld()->LineTraceSingleByChannel(drawInfo, startPos, endPos, ECC_GameTraceChannel10, params);
		bool isdraw = GetWorld()->LineTraceSingleByChannel(drawInfo, startPos, endPos, ECC_GameTraceChannel10, params);
		if (isdraw == true)
		{
			PRINTTOScreen(FString::Printf(TEXT("WhiteBoard")));
			isdraw = UGameplayStatics::FindCollisionUV(drawInfo, 0, locationToDraw);
			postit = Cast<APostit>(drawInfo.GetActor());
			DrawDebugLine(GetWorld(), startPos, endPos, FColor::Red, false, -1, 0, -1);
			
			postit->Drawing();
		}

	}
	
	//if (isdraw && M_Marker)
	//{
	//	PRINTTOScreen(FString::Printf(TEXT("Overlap")));
	//	postit = Cast<APostit>(drawInfo.GetActor());
	//	DrawDebugLine(GetWorld(), startPos, endPos, FColor::Red, false, -1, 0, -1);
	//	isMarker = true;
		//postit->Drawing();
		//if (postit !=nullptr )
		//{

				//postit->Drawing();
				//RangeDecal = UGameplayStatics::SpawnDecalAtLocation(this, M_Marker, NewSize, startPos, NewRotator, 0.0f);
				//RangeDecal->SetRelatipostit = Cast<APostit>(drawInfo.GetActor());
	//	DrawDebugLine(GetWorld(), startPos, endPos, FColor::Red, false, -1, 0, -1);veRotation(NewRotator);
				//RangeDecal->SetRelativeScale3D(FVector(0.05f));
				//SetFadeOut(0.0f, 1.0f);
		//}
	//}
	
}


