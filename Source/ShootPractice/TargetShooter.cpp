// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetShooter.h"
#include "TimerManager.h"
// Sets default values
ATargetShooter::ATargetShooter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
}

// Called when the game starts or when spawned
void ATargetShooter::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &ATargetShooter::ShootTarget, 1, true, 0);
}

// Called every frame
void ATargetShooter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATargetShooter::ShootTarget() {
	UWorld* world = GetWorld();
	if (world) {
		FActorSpawnParameters param;
		param.Owner = this;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		FVector location = GetActorLocation()+FVector(0,0,100);
		float rotationRand = FMath::RandRange(20, 65);
		FRotator rotation = FRotator(rotationRand,90,45);
		world->SpawnActor(content, &location , &rotation, param);
	}
}