// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Target.generated.h"
class UProjectileMovementComponent;
UCLASS()
class SHOOTPRACTICE_API ATarget : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATarget();
	UPROPERTY(VisibleDefaultsOnly)
		UStaticMeshComponent* mesh;
	UPROPERTY(EditDefaultsOnly)
		UProjectileMovementComponent* projectile;
	UPROPERTY(VisibleDefaultsOnly)
		USceneComponent* scene;
	UPROPERTY(EditDefaultsOnly)
		UParticleSystem* particle;
	UFUNCTION()
	void GetScore(AActor* Shooter1);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
