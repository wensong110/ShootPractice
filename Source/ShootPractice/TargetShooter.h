// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Target.h"
#include "TargetShooter.generated.h"
UCLASS()
class SHOOTPRACTICE_API ATargetShooter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATargetShooter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
	void ShootTarget();
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ATarget> content;
	FTimerHandle MemberTimerHandle;
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* mesh;
};
