// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShootPracticeGameMode.generated.h"
class ATarget;
class ATargetShooter;
UCLASS(minimalapi)
class AShootPracticeGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AShootPracticeGameMode();
	UFUNCTION()
	void updateScore();
	UPROPERTY(BlueprintReadOnly)
	UUserWidget* userWidget;
	UFUNCTION(BlueprintCallable)
	void nextRound();
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> target;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ATargetShooter> targetShooter;
	UFUNCTION()
	void Round1();
	UFUNCTION()
	void Round2();
	void BeginPlay() override;
};



