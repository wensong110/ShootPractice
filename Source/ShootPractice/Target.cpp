// Fill out your copyright notice in the Description page of Project Settings.


#include "Target.h"
#include "ShootPracticeCharacter.h"
#include "MyPlayerState.h"
#include "GameFramework/ProjectileMovementComponent.h"
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
	mesh->AttachTo(scene);
	mesh->OnComponentHit.AddDynamic(this,&ATarget::OnHit);
	this->projectile->ProjectileGravityScale = 0;
	this->projectile->InitialSpeed = 0;
	this->projectile->MaxSpeed = 0;
	AActor* owner = GetOwner();
	if (1) {
		this->projectile->ProjectileGravityScale = 1;
		float spend = FMath::RandRange(1000, 2000);
		this->projectile->InitialSpeed = spend;
		this->projectile->MaxSpeed = spend;
		InitialLifeSpan = 3.0f;
	}
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
void ATarget::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	AShootPracticeCharacter* Shooter =Cast<AShootPracticeCharacter>(OtherActor->GetOwner());
	if (Shooter) {
		Cast<AMyPlayerState>(Shooter->GetPlayerState())->AddScore();
	}
	OtherActor->Destroy();
}