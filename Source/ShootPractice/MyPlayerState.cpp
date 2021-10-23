// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerState.h"

void AMyPlayerState::AddScore()
{
	this->SetScore(this->GetScore() + 1.0);
}