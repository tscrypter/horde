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
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* LM_SessionTitleTextBlock;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* LM_MapTitleTextBlock;

	UPROPERTY(meta = (BindWidget))
	class UImage* LM_MapThumbnail;

	UPROPERTY(meta = (BindWidget))
	UPlayerGrid* LM_PlayerGrid;

	UPROPERTY(meta = (BindWidget))
	class UButton* LM_LeaveButton; // Transition to MainMenu map

	UPROPERTY(meta = (BindWidget))
	class UButton* LM_ReadyButton; // When all players are ready, launch match
	
};
