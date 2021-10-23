// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameStateBase.h"

void AMyGameStateBase::nextRound() {
	round++;
	if (round == 2) {
		UWorld* world=GetWorld();
		if (world) {
			//world->SpawnActor();
		}
	}
}