// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MyGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTPRACTICE_API AMyGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
private:
public:
	UPROPERTY(BlueprintReadOnly)
	int round = 1;
	UFUNCTION(BlueprintCallable)
	void nextRound();
};
