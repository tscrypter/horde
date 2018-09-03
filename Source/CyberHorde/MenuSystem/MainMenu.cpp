// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"
#include "OnlineSessionSettings.h"

UMainMenu::UMainMenu(const FObjectInitializer & ObjectInitializer)
{

}

bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(MM_SinglePlayerButton != nullptr)) return false;
	MM_SinglePlayerButton->OnClicked.AddDynamic(this, &UMainMenu::OpenSingleplayerMenu);

	if (!ensure(SP_CancelButton != nullptr)) return false;
	SP_CancelButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);

	return true;
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
	MenuSwitcher->SetActiveWidget(MainScreen);
}

void UMainMenu::OpenSingleplayerMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(MainScreen != nullptr)) return;
	if (!ensure(SinglePlayerScreen != nullptr)) return;
	MenuSwitcher->SetActiveWidget(SinglePlayerScreen);
}
