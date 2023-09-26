// Fill out your copyright notice in the Description page of Project Settings.


#include "PointVolume.h"
#include "Components/BoxComponent.h"

// Sets default values
APointVolume::APointVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxVolume = CreateDefaultSubobject<UBoxComponent>("BoxVolume");
	RootComponent = BoxVolume;

}

// Called when the game starts or when spawned
void APointVolume::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APointVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APointVolume::GetCandidatePoints(TArray<FVector>& OutPoints)
{

}

