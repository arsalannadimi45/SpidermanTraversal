// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputAction.h"
#include "InputConfigData.generated.h"

/**
 * Store pointer to input action for native binding
 */
UCLASS()
class SPIDERMANTRAVERSAL_API UInputConfigData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UInputAction* Movement_IA;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UInputAction* Look_IA;
};
