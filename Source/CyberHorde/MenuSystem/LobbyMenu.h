// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuSystem/MenuWidget.h"
#include "PlayerGrid.h"
#include "LobbyMenu.generated.h"

/**
 * 
 */
UCLASS()
class CYBERHORDE_API ULobbyMenu : public UMenuWidget
{
	GENERATED_BODY()
	
public:
	ULobbyMenu(const FObjectInitializer & ObjectInitializer);
		
private:
	// Controls for lobby menu
	//UPROPERTY(meta = (BindWidget))
	//class UTextBlock* LM_SessionTitleTextBlock; // Display name of session

	//UPROPERTY(meta = (BindWidget))
	//class UButton* HM_SelectLevelButton; // Navigate to level select screen

	//UPROPERTY(meta = (BindWidget))
	//class UTextBlock* LM_MapTitleTextBlock; // Display title of selected map

	//UPROPERTY(meta = (BindWidget))
	//class UImage* LM_MapThumbnail; // Display thumbnail of selected map

	//UPROPERTY(meta = (BindWidget))
	//UPlayerGrid* LM_PlayerGrid;    // Displays players in the lobby and pending invites

	//UPROPERTY(meta = (BindWidget))
	//class UButton* LM_LeaveButton; // Transition to MainMenu map

	//UPROPERTY(meta = (BindWidget))
	//class UButton* LM_ReadyButton; // When all players are ready, launch match
	
};
