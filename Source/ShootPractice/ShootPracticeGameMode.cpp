// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShootPracticeGameMode.h"

#include "MyGameStateBase.h"
#include "ShootPracticeHUD.h"
#include "ShootPracticeCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "MyPlayerState.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"

AShootPracticeGameMode::AShootPracticeGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AShootPracticeHUD::StaticClass();
	PlayerStateClass = AMyPlayerState::StaticClass();
	GameStateClass = AMyGameStateBase::StaticClass();
	static ConstructorHelpers::FClassFinder<UUserWidget> scoreWidget(TEXT("/Game/FirstPersonCPP/Blueprints/WBP_Score"));
	userWidget=CreateWidget(Super::GetWorld(),scoreWidget.Class);
	if(userWidget) userWidget->AddToViewport();
}

void AShootPracticeGameMode::updateScore()
{
	AMyGameStateBase* gamestate=GetGameState<AMyGameStateBase>();
	if(gamestate)
	{
		auto text=Cast<UTextBlock>(userWidget->GetWidgetFromName(FName(TEXT("TextBlock_0"))));
		text->SetText((FText::FromString(FString(TEXT("得分:"))+FString::FromInt(gamestate->score))));
		if(gamestate->score<10)
		{
			Round1();
		}
		if(gamestate->score==10)
		{
			nextRound();
			Round2();
		}
	}
}
void AShootPracticeGameMode::nextRound() {
	AMyGameStateBase* gamestate=GetGameState<AMyGameStateBase>();
	if(gamestate) gamestate->round++;
}

void AShootPracticeGameMode::Round1()
{
	AMyGameStateBase* gamestate=GetGameState<AMyGameStateBase>();
	if(gamestate&&gamestate->round==1)
	{
		UWorld* world=GetWorld();
		if(world)
		{
			FVector postion=FVector(0,0,0);
			postion=postion+FVector(FMath::RandRange(-1000,1000),FMath::RandRange(-1000,1000),500);
			world->SpawnActor(target,&postion);
		}
	}
}

void AShootPracticeGameMode::Round2()
{
	UWorld* world=GetWorld();
	if(world)
	{
		FVector postion=FVector(-1100,-1200,200);
		world->SpawnActor(targetShooter,&postion);
	}
}

void AShootPracticeGameMode::BeginPlay()
{
	Super::BeginPlay();
	Round1();
}
