// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"
#include "OnlineSessionInterface.h"
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
	void InGameLoadMenu();

	UFUNCTION(Exec)
	void Host() override;

	UFUNCTION(Exec)
	void Join(uint32 Index) override;

	UFUNCTION(Exec)
	void GetSessions() override;

	virtual void LoadMainMenu() override;

private:
	bool bIsTraveling = false;
	bool bIsLan = true;
	bool bUseLobbies = true;
	bool bIsSearchable = true;
	bool bFriendsOnly = false;
	bool bLetPublicJoin = true;
	uint32 iNumPrivateConnections = 5;
	uint32 iNumPublicConnections = 5;
	uint32 iMaxSearchResults = 100;

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
