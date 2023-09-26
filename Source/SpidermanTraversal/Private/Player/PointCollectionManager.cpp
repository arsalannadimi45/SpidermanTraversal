// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PointCollectionManager.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PointVolume.h"
#include "Engine/World.h"

// Sets default values
APointCollectionManager::APointCollectionManager():
	IdealSwingLength(2000.f),
	IdealSwingSlope(45.f),
	SwingAttachErrorTolerance(800.f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<USphereComponent>("Collider");
	RootComponent = Collider;  

}

// Called when the game starts or when spawned
void APointCollectionManager::BeginPlay()
{
	Super::BeginPlay();

	if (!PlayerPawn)
	{
		PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	}
}

// Called every frame
void APointCollectionManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateIdealPointLocation();
}

void APointCollectionManager::RegisterPointVolume(APointVolume* PointVolume)
{
	if (PointVolume)
	{
		PointVolumes.AddUnique(PointVolume);
	}
}

void APointCollectionManager::UnregisterPointVolume(APointVolume* PointVolume)
{
	if (PointVolume)
	{
		PointVolumes.Remove(PointVolume);
	}
}

void APointCollectionManager::RegisterPoint(FVector& Point)
{
		SwingPoints.AddUnique(Point);
}

void APointCollectionManager::UnregisterPoint(FVector& Point)
{
		SwingPoints.Remove(Point);
}

void APointCollectionManager::UpdateSwingPoints()
{

}

void APointCollectionManager::UpdateBestSwingPoint()
{

}

void APointCollectionManager::UpdateIdealPointLocation()
{
	if (PlayerPawn)
	{
		const APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
		if (PlayerController) 
		{
			const FRotator ControlRotation = PlayerController->GetControlRotation();
			const FVector IdealSwingDirection = ControlRotation.Vector().RotateAngleAxis(IdealSwingSlope, FVector::UpVector);


			TArray<AActor*> ActorsToIgnore; 
			ActorsToIgnore.Add(PlayerPawn);

			FVector Start = PlayerPawn->GetActorLocation();
			FVector End = Start + IdealSwingDirection * IdealSwingLength;
			FHitResult HitResult;

			bool bBlockingHit = UKismetSystemLibrary::SphereTraceSingle(this,Start,End,20.f,ETraceTypeQuery::TraceTypeQuery1,false,ActorsToIgnore,EDrawDebugTrace::ForOneFrame,HitResult,true);

	//		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 50.f, 20, FColor::Purple, false, 0.05f, 0, 3.f);
		}
	}
}

