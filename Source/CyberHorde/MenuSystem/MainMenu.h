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

	void SetLevelList(TArray<FLevelStruct> Levels);

	void SetServerList(TArray<FOnlineSessionSearchResult> ServerNames);

	void SelectServer(FString SessionIdStr);

	bool Initialize();
	
private:
	TSubclassOf<class UUserWidget> ServerRowClass;

	// Screens
	UPROPERTY(meta = (BindWidget))
	class UWidget* MainScreen;

	UPROPERTY(meta = (BindWidget))
	class UWidget* SinglePlayerScreen;

	UPROPERTY(meta = (BindWidget))
	class UWidget* LevelSelectScreen;

	UPROPERTY(meta = (BindWidget))
	class UWidget* MultiplayerScreen;

	UPROPERTY(meta = (BindWidget))
	class UWidget* HostScreen;

	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinScreen;

	// Widget for switching screens
	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher;	// Switch between which menu is displayed

	// Controls for the first screen (single player, multiplayer, options, and quit)
	UPROPERTY(meta = (BindWidget))
	class UButton* MM_SinglePlayerButton;	// Navigate to single player screen

	UPROPERTY(meta = (BindWidget))
	class UButton* MM_MultiplayerButton;	// Navigate to multiplayer screen

	// TODO: Figure out what options we'd like to offer
	//UPROPERTY(meta = (BindWidget))
	//class UButton* MM_OptionsButton;	// Navigate to options menu

	UPROPERTY(meta = (BindWidget))
	class UButton* MM_QuitButton;	// Quit to the desktop game

	// Controls for singleplayer screen
	UPROPERTY(meta = (BindWidget))
	class UButton* SP_LevelSelectButton;	// Navigate to level select screen
	
	UPROPERTY(meta = (BindWidget))
	class UButton* SP_IncreaseSquadSizeButton;	// Increase size of squad members in single player match

	UPROPERTY(meta = (BindWidget))
	class UButton* SP_DecreaseSquadSizeButton;	// Decreas size of squad members in single player match
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SP_MapTitleTextBlock;	// Display title of selected single player map

	UPROPERTY(meta = (BindWidget))
	class UImage* SP_MapThumbnail;	// Display thumbnail of selected single player map


	UPROPERTY(meta = (BindWidget))
	UPlayerGrid* SP_SquadGrid;	// Display squad members

	UPROPERTY(meta = (BindWidget))
	class UButton* SP_StartButton;	// Launch map, passing in AI for remaining squad members

	UPROPERTY(meta = (BindWidget))
	class UButton* SP_CancelButton;	//	Navigate to main screen

	// Controls for multiplayer screen
	UPROPERTY(meta = (BindWidget))
	class UButton* MP_HostButton;	// Navigate to host screen

	UPROPERTY(meta = (BindWidget))
	class UButton* MP_JoinButton;	// Navigate to join screen

	UPROPERTY(meta = (BindWidget))
	class UButton* MP_CancelButton;	// Navigate to main screen

	//// Controls for host menu

	//UPROPERTY(meta = (BindWidget))
	//class UCheckBox* HM_InviteOnlyCheckBox;	// Don't advertise, must have invite to join

	//UPROPERTY(meta = (BindWidget))
	//class UCheckBox* HM_FriendsOnlyCheckBox;	// Advertise, but only allow friends to join

	//UPROPERTY(meta = (BindWidget))
	//class UTextBlock* HM_SquadSizeTextBlock;	// Display target squad size

	//UPROPERTY(meta = (BindWidget))
	//class UButton* HM_IncreaseSquadSizeButton;	// Increase the squad size

	//UPROPERTY(meta = (BindWidget))
	//class UButton* HM_DecreaseSquadSizeButton;	// Decrease the squad size

	//UPROPERTY(meta = (BindWidget))
	//UPlayerGrid* HM_PlayerGrid;		// Display Squad Size

	//UPROPERTY(meta = (BindWidget))
	//class UButton* HM_CancelButton;	// Navigate to multiplayer screen

	//UPROPERTY(meta = (BindWidget))
	//class UButton* HM_StartButton; // Create session and transition to Lobby map

	//// Controls for join menu
	//UPROPERTY(meta = (BindWidget))
	//class UPanelWidget* JM_ServerList;	// List advertised sessions

	//UPROPERTY(meta = (BindWidget))
	//class UButton* JM_CancelButton;	// Navigate to multiplayer screen

	//UPROPERTY(meta = (BindWidget))
	//class UButton* JM_JoinButton;	// Join session and transition to Lobby map

	// Open menus
	UFUNCTION()
	void OpenMainMenu();

	UFUNCTION()
	void OpenSingleplayerMenu();

	UFUNCTION()
	void OpenMultiplayerMenu();



	// Shared callbacks
	UFUNCTION()
	void IncreaseSquadSize();

	UFUNCTION()
	void DecreaseSquadSize();


	// Launch Levels
	UFUNCTION()
	void LaunchSingleplayerLevel();


	// Set Level
	UFUNCTION()
	void SetSingleplayerLevel(FLevelStruct Level);

};