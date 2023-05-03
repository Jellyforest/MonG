// Fill out your copyright notice in the Description page of Project Settings.


#include "CleaningEffect.h"
#include <Components/SphereComponent.h>
#include <NiagaraComponent.h>
#include <Kismet/GameplayStatics.h>
#include "MonGPlayer.h"


// Sets default values
ACleaningEffect::ACleaningEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	fx_Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("fxSphere"));
	SetRootComponent(RootComponent);
	clean_effect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("cleaneffect"));
	clean_effect->SetupAttachment(fx_Sphere);
}

// Called when the game starts or when spawned
void ACleaningEffect::BeginPlay()
{
	Super::BeginPlay();
	player= Cast<AMonGPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), AMonGPlayer::StaticClass()));
}

// Called every frame
void ACleaningEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (player->isClean == false)
	{
		Destroy();
	}
}

void ACleaningEffect::CleanTimeOff()
{
	


}

//»Æ¿Œ
