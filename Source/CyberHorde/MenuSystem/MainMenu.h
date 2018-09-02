// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuSystem/MenuWidget.h"
#include "PlayerGrid.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class CYBERHORDE_API UMainMenu : public UMenuWidget
{
	GENERATED_BODY()
	
public:
	UMainMenu(const FObjectInitializer & ObjectInitializer);

	void SetServerList(TArray<FOnlineSessionSearchResult> ServerNames);

	void SelectServer(FString SessionIdStr);
	
private:
	TSubclassOf<class UUserWidget> ServerRowClass;

	// Widget for switching screens
	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher;

	// Controls for the first screen (single player, multiplayer, options, and quit)
	UPROPERTY(meta = (BindWidget))
	class UButton* MM_SinglePlayerButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* MM_MultiplayerButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* MM_OptionsButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* MM_QuitButton;

	// Controls for singleplayer screen
	UPROPERTY(meta = (BindWidget))
	class UButton* SP_LevelSelectButton;

	UPROPERTY(meta = (BindWidget))
	class UCheckBox* SP_FillPartyWithBotsCheckBox;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SP_MapTitleTextBlock;

	UPROPERTY(meta = (BindWidget))
	class UImage* SP_MapThumbnail;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SP_MaxPlayersTextBlock;

	UPROPERTY(meta = (BindWidget))
	class UButton* SP_IncreaseMaxPlayersButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* SP_DecreaseMaxPlayersButton;

	UPROPERTY(meta = (BindWidget))
	UPlayerGrid* SP_PlayerGrid;

	UPROPERTY(meta = (BindWidget))
	class UButton* SP_StartButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* SP_CancelButton;
		
	
	// Controls for multiplayer screen
	UPROPERTY(meta = (BindWidget))
	class UButton* MP_HostButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* MP_JoinButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* MP_Multiplayer_CancelButton;

	// Controls for host menu
	UPROPERTY(meta = (BindWidget))
	class UButton* HM_SelectLevelButton;

	UPROPERTY(meta = (BindWidget))
	class UCheckBox* HM_InviteOnlyCheckBox;

	UPROPERTY(meta = (BindWidget))
	class UCheckBox* HM_FriendsOnlyCheckBox;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* HM_MaxPlayersTextBlock;

	UPROPERTY(meta = (BindWidget))
	class UButton* HM_IncreaseMaxPlayersButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* HM_DecreaseMaxPlayersButton;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* HM_MapTitleTextBlock;

	UPROPERTY(meta = (BindWidget))
	class UImage* HM_MapThumbnail;

	UPROPERTY(meta = (BindWidget))
	UPlayerGrid* HM_PlayerGrid;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* HM_CancelButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* HM_StartButton; // Transition to Lobby map

	// Controls for join menu
	UPROPERTY(meta = (BindWidget))
	class UPanelWidget* JM_ServerList;

	UPROPERTY(meta = (BindWidget))
	class UButton* JM_CancelButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* JM_JoinButton;

	

};
