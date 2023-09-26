// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PointVolume.generated.h"

class UBoxComponent;

UCLASS()
class SPIDERMANTRAVERSAL_API APointVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APointVolume();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* BoxVolume;  

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void GetCandidatePoints(TArray<FVector>& OutPoints);

};
