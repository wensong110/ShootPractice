// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SnipeCharacter.generated.h"

UCLASS()
class SHOOTPRACTICE_API ASnipeCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASnipeCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate=6;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate=6;

	FVector2D MoveOffset;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location);
	UFUNCTION(BlueprintCallable)
	void TurnAtRate(float Rate);
	UFUNCTION(BlueprintCallable)
	void LookUpAtRate(float Rate);
	UFUNCTION(BlueprintImplementableEvent)
	void OnFire();
	UFUNCTION(BlueprintImplementableEvent)
	void OpenScope();
	UFUNCTION(BlueprintImplementableEvent)
	void CloseScope();
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> Projectile;
	FVector PreLocation;
	ETouchIndex::Type PreIndex;
};
