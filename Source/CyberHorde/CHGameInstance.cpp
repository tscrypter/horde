// Fill out your copyright notice in the Description page of Project Settings.

#include "CHGameInstance.h"

#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/PlayerController.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "OnlineSessionInterface.h"

UCHGameInstance::UCHGameInstance(const FObjectInitializer & ObjectInitializer)
{
	// TODO: Construct instances of main menu and in game menu objects
}

void UCHGameInstance::Init()
{
	bIsTraveling = false;
	IOnlineSubsystem* SubSystem = IOnlineSubsystem::Get();
	if (SubSystem != nullptr)
	{
		if (*SubSystem->GetSubsystemName().ToString() == FString("NULL"))
		{
			bIsLan = true;
		}
		else
		{
			bIsLan = false;
		}

		SessionInterface = SubSystem->GetSessionInterface();

		if (SessionInterface.IsValid())
		{
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UCHGameInstance::OnCreateSessionComplete);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UCHGameInstance::OnDestroySessionCompleteDelegate);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UCHGameInstance::OnFindSessionsComplete);
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UCHGameInstance::OnJoinSessionComplete);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Found no subsystem"));
	}
}

void UCHGameInstance::LoadMenuWidget()
{
	// TODO: Load main menu
}

void UCHGameInstance::InGameLoadMenu()
{
	// TODO: Load pause menu
}

void UCHGameInstance::Host()
{
	if (SessionInterface.IsValid())
	{
		FOnlineSession* ExistingSession = SessionInterface->GetNamedSession(SessionName);
		if (ExistingSession != nullptr)
		{
			SessionInterface->DestroySession(SessionName);
		}
		else
		{
			CreateSession(SessionName);
		}
	}
}

void UCHGameInstance::Join(uint32 Index)
{
	if (!SessionInterface.IsValid()) return;
	if (!SessionSearch.IsValid()) return;

	// TODO: Teardown menu after it's been created if it's not null

	SessionInterface->JoinSession(0, SessionName, SessionSearch->SearchResults[Index]);

}

void UCHGameInstance::GetSessions()
{
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	if (SessionSearch.IsValid())
	{
		SessionSearch->bIsLanQuery = bIsLan;
		SessionSearch->MaxSearchResults = iMaxSearchResults;
		if (bUseLobbies)
		{
			SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
		}
		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
		UE_LOG(LogTemp, Warning, TEXT("Started search for sessions"));
	}
}

void UCHGameInstance::LoadMainMenu()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel("/Game/MenuSystem/MainMenu", ETravelType::TRAVEL_Absolute);
}

void UCHGameInstance::CreateSession(FName SessionName)
{
	FOnlineSessionSettings SessionSettings;
	SessionSettings.bIsLANMatch = bIsLan;
	SessionSettings.NumPublicConnections = iNumPublicConnections;
	SessionSettings.NumPrivateConnections = iNumPrivateConnections;
	SessionSettings.bShouldAdvertise = bIsSearchable;
	SessionSettings.bUsesPresence = bUseLobbies;
	SessionSettings.bAllowJoinViaPresenceFriendsOnly = (bUseLobbies && bFriendsOnly);
	SessionSettings.bAllowJoinViaPresence = (bUseLobbies && bLetPublicJoin);

	SessionSettings.bAllowJoinInProgress = true;
	SessionSettings.bAllowInvites = true;

	SessionInterface->CreateSession(0, SessionName, SessionSettings);
	UE_LOG(LogTemp, Warning, TEXT("Making request to create session"));
}

void UCHGameInstance::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		UE_LOG(LogTemp, Warning, TEXT("Finished creating session"));
		// TODO: Teardown menu if it's not null

		UEngine* Engine = GetEngine();
		if (!ensure(Engine != nullptr)) return;

		
		UWorld* World = GetWorld();
		if (!ensure(World != nullptr)) return;
		bIsTraveling = true;
		World->ServerTravel("/Game/MenuSystem/LobbyMenu?listen");
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Failed to create session "));
	}
}

void UCHGameInstance::OnFindSessionsComplete(bool bWasSuccessful)
{
	UE_LOG(LogTemp, Warning, TEXT("Finished search for sessions"));
	if (bWasSuccessful) {
		UE_LOG(LogTemp, Warning, TEXT("Successfully searched for sessions"));
		TArray<FOnlineSessionSearchResult> SearchResults = SessionSearch->SearchResults;


		// If not traveling and menu isn't null, set the server list on the menu
		
		for (FOnlineSessionSearchResult& SearchResult : SearchResults)
		{
			if (SearchResult.IsValid()) {
				UE_LOG(LogTemp, Warning, TEXT("Found session named: %s"), *SearchResult.GetSessionIdStr());
			}
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Something went wrong while searching for sessions"));
	}
}

void UCHGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (!SessionInterface.IsValid()) return;
	if (!SessionSearch.IsValid()) return;

	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;


	FString Address;
	if (!SessionInterface->GetResolvedConnectString(SessionName, Address))
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not get connect string."))
	}

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;
	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}

void UCHGameInstance::OnDestroySessionCompleteDelegate(FName SessionName, bool bWasSuccessful)
{
	if (bWasSuccessful) {
		UE_LOG(LogTemp, Warning, TEXT("Successfully destroyed session"));
		Host();
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Failed to destroy session"));

	}
}
