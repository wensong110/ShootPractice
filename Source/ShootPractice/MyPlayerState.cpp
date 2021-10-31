// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerState.h"

#include "MyGameStateBase.h"
#include "ShootPracticeGameMode.h"

void AMyPlayerState::AddScore()
{
	this->SetScore(this->GetScore() + 1.0);
	auto gamestate=GetWorld()->GetGameState();
	auto gamemode=GetWorld()->GetAuthGameMode();
	if(gamestate&&gamemode)
	{
		AMyGameStateBase* myGameState=Cast<AMyGameStateBase>(gamestate);
		if(myGameState)
		{
			myGameState->addScore();
		}
		AShootPracticeGameMode* myGameMode=Cast<AShootPracticeGameMode>(gamemode);
		if(myGameMode)
		{
			myGameMode->updateScore();
		}
	}
}
