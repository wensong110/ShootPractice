// Fill out your copyright notice in the Description page of Project Settings.


#include "SnipeCharacter.h"

// Sets default values
ASnipeCharacter::ASnipeCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASnipeCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASnipeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TurnAtRate(MoveOffset.X);
	LookUpAtRate(MoveOffset.Y);
}

// Called to bind functionality to input
void ASnipeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ASnipeCharacter::BeginTouch);
	PlayerInputComponent->BindTouch(EInputEvent::IE_Released, this, &ASnipeCharacter::EndTouch);
	PlayerInputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ASnipeCharacter::TouchUpdate);
}

void ASnipeCharacter::BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	OpenScope();
	PreIndex=FingerIndex;
	PreLocation=Location;
}

void ASnipeCharacter::EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if(PreIndex==FingerIndex)
	{
		OnFire();
		CloseScope();
		PreLocation=Location;
	}
	MoveOffset=FVector2D(0,0);
}

void ASnipeCharacter::TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if(PreIndex==FingerIndex)
	{
		FVector2D Cha=FVector2D(Location.X-PreLocation.X,Location.Y-PreLocation.Y);
		MoveOffset=MoveOffset*0.7+Cha*0.3;
	}
	PreLocation=Location;
}

void ASnipeCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ASnipeCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

