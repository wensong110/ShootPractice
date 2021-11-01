// Fill out your copyright notice in the Description page of Project Settings.


#include "Target.h"
#include "ShootPracticeCharacter.h"
#include "MyPlayerState.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TargetShooter.h"
// Sets default values
ATarget::ATarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	scene = CreateDefaultSubobject<USceneComponent>(TEXT("scene"));
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	projectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("projectileMove"));
	RootComponent = scene;
	mesh->AttachToComponent(scene,FAttachmentTransformRules::KeepRelativeTransform);
	//mesh->OnComponentHit.AddDynamic(this,&ATarget::OnHit);
}

// Called when the game starts or when spawned
void ATarget::BeginPlay()
{
	Super::BeginPlay();
	this->SetActorRotation(FRotator(0, 0, 0));
	this->SetActorScale3D(FVector(2, 2, 2));
}

// Called every frame
void ATarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void ATarget::GetScore(AActor* Shooter1) {
	AShootPracticeCharacter* Shooter = Cast<AShootPracticeCharacter>(Shooter1);
	if (Shooter) {
		Cast<AMyPlayerState>(Shooter->GetPlayerState())->AddScore();
		GEngine->AddOnScreenDebugMessage(7, 1, FColor::Red,FString::FromInt(Shooter->GetPlayerState()->GetScore()));
	}
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), particle, GetActorLocation(), GetActorRotation());
	Destroy();
}