// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "../CHStructs.h"

#include "MenuInterface.generated.h"

// This class does not need to be modified
UINTERFACE(MinimalAPI)
class UMenuInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CYBERHORDE_API IMenuInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void LaunchSingleplayer() = 0;
	
	virtual void Host() = 0;
	virtual void Join(uint32 Index) = 0;
	virtual void LoadMainMenu() = 0;
	virtual void GetSessions() = 0;
	
	virtual void SetSquadSize(uint16 InSize) = 0;
	virtual void RefreshSquad() = 0;
	virtual TArray<FPlayerData> GetSquad() = 0;
	virtual void AddPlayerToSquad(FPlayerData PlayerData) = 0;


	virtual void SetSingleplayerMap(FLevelStruct SelectedLevel) = 0;
	virtual FLevelStruct GetSingleplayerMap() = 0;
	virtual void SetMultiplayerMap(FLevelStruct SelectedLevel) = 0;
	virtual FLevelStruct GetMultiplayerMap() = 0;
	
};
