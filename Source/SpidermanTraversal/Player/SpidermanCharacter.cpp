// Fill out your copyright notice in the Description page of Project Settings.

#include "SpidermanTraversal/Player/SpidermanCharacter.h"

// Sets default values
ASpidermanCharacter::ASpidermanCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpidermanCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpidermanCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASpidermanCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

