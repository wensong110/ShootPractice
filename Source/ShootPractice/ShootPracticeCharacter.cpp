// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShootPracticeCharacter.h"
#include "ShootPracticeProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Target.h"


AShootPracticeCharacter::AShootPracticeCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->SetOnlyOwnerSee(false);			// otherwise won't be visible in the multiplayer
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	FP_Gun->SetupAttachment(RootComponent);

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, 10.0f);

	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P, FP_Gun, and VR_Gun 
	// are set in the derived blueprint asset named MyCharacter to avoid direct content references in C++.
}

void AShootPracticeCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
}

//////////////////////////////////////////////////////////////////////////
// Input

void AShootPracticeCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AShootPracticeCharacter::StartFire);
	PlayerInputComponent->BindAction("Fire",IE_Released,this,&AShootPracticeCharacter::EndFire);
	// Enable touchscreen input

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AShootPracticeCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AShootPracticeCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AShootPracticeCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AShootPracticeCharacter::LookUpAtRate);
	EnableTouchscreenMovement(PlayerInputComponent);
}

void AShootPracticeCharacter::OnFire()
{
	// try and fire a projectile
	AActor* target1 = BulletTrace();
	ATarget* target = Cast<ATarget>(target1);
	if (target) {
		target->GetScore(this);
	}
	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}
	if (FireAnimation != nullptr)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}

void AShootPracticeCharacter::BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D Size;
	GWorld->GetGameViewport()->GetViewportSize(Size);
	if ( Location.X>Size.X*0.8 && Location.Y>Size.Y*0.8 )
	{
		TouchItem.FingerIndex=FingerIndex;
		StartFire();
	}
	TouchItem.bIsPressed = true;
	TouchItem.Location = Location;
	TouchItem.bMoved = false;
}

void AShootPracticeCharacter::EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == false)
	{
		return;
	}
	if ((FingerIndex == TouchItem.FingerIndex))
	{
		EndFire();
	}
	TouchItem.bIsPressed = false;
	TouchItem.Location=Location;
}

void AShootPracticeCharacter::TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	const FVector2D Move=FVector2D(Location.X-TouchItem.Location.X,Location.Y-TouchItem.Location.Y);
	if(FMath::Abs(Move.X)>0||FMath::Abs(Move.Y)>0)
	{
		TouchItem.bMoved=true;
		LookUpAtRate(Move.Y*0.05);
		TurnAtRate(Move.X*0.05);
	}else
	{
		TouchItem.bMoved=false;
	}
	TouchItem.Location=Location;
}

void AShootPracticeCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AShootPracticeCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AShootPracticeCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AShootPracticeCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

bool AShootPracticeCharacter::EnableTouchscreenMovement(class UInputComponent* PlayerInputComponent)
{

	//if (FPlatformMisc::SupportsTouchInput() || GetDefault<UInputSettings>()->bUseMouseForTouch)
	{
		PlayerInputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AShootPracticeCharacter::BeginTouch);
		PlayerInputComponent->BindTouch(EInputEvent::IE_Released, this, &AShootPracticeCharacter::EndTouch);
		PlayerInputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AShootPracticeCharacter::TouchUpdate);
		return true;
	}
	
	return false;
}
AActor* AShootPracticeCharacter::BulletTrace() {
	FHitResult hitResult(ForceInit);
	FVector pos, direct;
	FCollisionQueryParams param(FName(TEXT("traceParam")), true);
	param.AddIgnoredActor(this);
	param.bReturnPhysicalMaterial = false;
	param.bTraceComplex = false;
	pos=((FP_MuzzleLocation != nullptr) ? FP_MuzzleLocation->GetComponentLocation() : GetActorLocation()) + GetControlRotation().RotateVector(GunOffset);
	direct = FVector(1,0,0);
	direct = GetControlRotation().RotateVector(direct);
	GetWorld()->LineTraceSingleByChannel(hitResult, pos, pos + 8000 * direct, ECC_WorldDynamic, param);
	return hitResult.GetActor();
}

void AShootPracticeCharacter::ChangeGun(USkeletalMesh* newMesh)
{
	if(newMesh)
	{
		FP_Gun->SetSkeletalMesh(newMesh);
		FP_Gun->SetVisibility(true);
		//FP_Gun->SetRelativeRotation(FRotator(0,90,0));
	}
}
void AShootPracticeCharacter::StartFire()
{
	GetWorld()->GetTimerManager().SetTimer(Timer,this,&AShootPracticeCharacter::OnFire,0.3f,true,0);
}

void AShootPracticeCharacter::EndFire()
{
	GetWorld()->GetTimerManager().ClearTimer(Timer);
}