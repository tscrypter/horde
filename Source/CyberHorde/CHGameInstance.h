// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"
#include "OnlineSessionInterface.h"

#include "CHStructs.h"

#include "CHGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class CYBERHORDE_API UCHGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()
	
public:
	UCHGameInstance(const FObjectInitializer & ObjectInitializer);

	virtual void Init();

	UFUNCTION(BlueprintCallable)
	void LoadMenuWidget();

	UFUNCTION(BlueprintCallable)
	void InLobbyLoadMenu();

	UFUNCTION(BlueprintCallable)
	void InGameLoadMenu();

	UFUNCTION(Exec)
	void Host() override;

	UFUNCTION(Exec)
	void Join(uint32 Index) override;

	UFUNCTION(Exec)
	void GetSessions() override;

	UFUNCTION()
	void SetSingleplayerMap(FLevelStruct SelectedLevel) override;

	UFUNCTION()
	FLevelStruct GetSingleplayerMap() override;

	UFUNCTION()
	void SetMultiplayerMap(FLevelStruct SelectedLevel) override;

	UFUNCTION()
	FLevelStruct GetMultiplayerMap() override;

	UFUNCTION()
	void LaunchSingleplayer() override;

	UFUNCTION()
	void SetSquadSize(uint16 InSize) override;

	UFUNCTION()
	TArray<FPlayerData> GetSquad() override;

	UFUNCTION()
	void RefreshSquad() override;

	UFUNCTION()
	void AddPlayerToSquad(FPlayerData PlayerData);

	virtual void LoadMainMenu() override;

private:
	TSubclassOf<class UUserWidget> MainMenuClass;
	TSubclassOf<class UUserWidget> InGameMenuClass;
	TSubclassOf<class UUserWidget> LobbyMenuClass;

	class UMainMenu* Menu;
	class ULobbyMenu* LobbyMenu;

	FLevelStruct SingleplayerLevel;
	FLevelStruct MultiplayerLevel;
	uint16 iSquadSize;
	TArray<FPlayerData> Squad;

	bool bIsTraveling = false;
	bool bIsLan = true;
	bool bUseLobbies = true;
	bool bIsSearchable = true;
	bool bFriendsOnly = false;
	bool bLetPublicJoin = true;
	uint32 iNumPrivateConnections = 5;
	uint32 iNumPublicConnections = 5;
	uint32 iMaxSearchResults = 100;

	void OnConnectionStatusChangedDelegates(const FString& ServiceName, EOnlineServerConnectionStatus::Type LastConnectionState, EOnlineServerConnectionStatus::Type ConnectionState);

	IOnlineSessionPtr SessionInterface;

	void CreateSession(FName SessionName);
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnFindSessionsComplete(bool bWasSuccessful);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	void OnDestroySessionCompleteDelegate(FName SessionName, bool bWasSuccessful);


	const FName DEFAULT_SESSION_NAME = TEXT("My Session Game");
	FName SessionName = DEFAULT_SESSION_NAME;
	TSharedPtr<FOnlineSessionSearch> SessionSearch;
	
	
};
