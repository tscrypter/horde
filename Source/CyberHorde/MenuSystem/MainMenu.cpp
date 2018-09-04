// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"
#include "OnlineSessionSettings.h"

UMainMenu::UMainMenu(const FObjectInitializer & ObjectInitializer)
{

}

bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	// Main Menu screen events
	if (!ensure(MM_SinglePlayerButton != nullptr)) return false;
	MM_SinglePlayerButton->OnClicked.AddDynamic(this, &UMainMenu::OpenSingleplayerMenu);

	if (!ensure(MM_MultiplayerButton != nullptr)) return false;
	MM_MultiplayerButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMultiplayerMenu);

	// Singleplayer screen events
	if (!ensure(SP_CancelButton != nullptr)) return false;
	SP_CancelButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);

	if (!ensure(SP_StartButton != nullptr)) return false;
	SP_StartButton->OnClicked.AddDynamic(this, &UMainMenu::LaunchSingleplayerLevel);

	// Multiplayer screen events
	if (!ensure(MP_CancelButton != nullptr)) return false;
	MP_CancelButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);

	return true;
}

void UMainMenu::SetLevelList(TArray<FLevelStruct> Levels)
{
	// TODO: Create the level list

	// TODO: Remove, for now setting the level to the first level
	SetSingleplayerLevel(Levels[0]);
}

void UMainMenu::SetServerList(TArray<FOnlineSessionSearchResult> ServerNames)
{
}

void UMainMenu::SelectServer(FString SessionIdStr)
{
}

void UMainMenu::OpenMainMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(MainScreen != nullptr)) return;
	if (!ensure(SinglePlayerScreen != nullptr)) return;
	if (!ensure(MultiplayerScreen != nullptr)) return;
	MenuSwitcher->SetActiveWidget(MainScreen);
}

void UMainMenu::OpenSingleplayerMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(MainScreen != nullptr)) return;
	if (!ensure(SinglePlayerScreen != nullptr)) return;
	if (!ensure(MultiplayerScreen != nullptr)) return;

	MenuInterface->RefreshSquad();

	TArray<FPlayerData> Squad = MenuInterface->GetSquad();
	for (FPlayerData PlayerData : Squad)
	{
		SP_SquadGrid->AddPlayer(PlayerData);
	}
	
	MenuSwitcher->SetActiveWidget(SinglePlayerScreen);
}

void UMainMenu::OpenMultiplayerMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(MainScreen != nullptr)) return;
	if (!ensure(SinglePlayerScreen != nullptr)) return;
	if (!ensure(MultiplayerScreen != nullptr)) return;
	MenuSwitcher->SetActiveWidget(MultiplayerScreen);
}

void UMainMenu::IncreaseSquadSize()
{
	
}

void UMainMenu::DecreaseSquadSize()
{
}

void UMainMenu::LaunchSingleplayerLevel()
{
	MenuInterface->LaunchSingleplayer();
}

void UMainMenu::SetSingleplayerLevel(FLevelStruct Level)
{
	if (!ensure(SP_MapTitleTextBlock != nullptr)) return;
	
	SP_MapTitleTextBlock->SetText(FText::FromString(Level.LevelName));
	UTexture2D* Texture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *Level.LevelImage));
	SP_MapThumbnail->SetBrushFromTexture(Texture);

	MenuInterface->SetSingleplayerMap(Level);
}
