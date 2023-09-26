// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PointCollectionManager.generated.h"

class USphereComponent; 
class APointVolume;


UCLASS()
class SPIDERMANTRAVERSAL_API APointCollectionManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APointCollectionManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* Collider; 

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	TArray<APointVolume*> PointVolumes;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FVector> SwingPoints;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FVector BestSwingPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	APawn* PlayerPawn;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float IdealSwingSlope; 

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float IdealSwingLength;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float SwingAttachErrorTolerance;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/* Registering Swing Point Volumes */
	UFUNCTION(BlueprintCallable)
	void RegisterPointVolume(APointVolume* PointVolume);

	/* Unregistering Swing Point Volumes */
	UFUNCTION(BlueprintCallable)
	void UnregisterPointVolume(APointVolume* PointVolume);

	/* Registering Swing Point */
	UFUNCTION(BlueprintCallable)
	void RegisterPoint(FVector& Point);

	/* Unregistering Swing Point */
	UFUNCTION(BlueprintCallable)
	void UnregisterPoint(FVector& Point);

	UFUNCTION()
	void UpdateSwingPoints();

	UFUNCTION()
	void UpdateBestSwingPoint();

	void UpdateIdealPointLocation();
};
