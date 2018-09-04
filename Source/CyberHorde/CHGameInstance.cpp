// Fill out your copyright notice in the Description page of Project Settings.

#include "CHGameInstance.h"

#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "OnlineSessionInterface.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerState.h"

#include "MenuSystem/MainMenu.h"
#include "MenuSystem/LobbyMenu.h"
#include "MenuSystem/MenuWidget.h"

UCHGameInstance::UCHGameInstance(const FObjectInitializer & ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> MainMenuBPClass(TEXT("/game/MenuSystem/Blueprints/WBP_MainMenu"));
	if (!ensure(MainMenuBPClass.Class != nullptr)) return;
	MainMenuClass = MainMenuBPClass.Class;

	ConstructorHelpers::FClassFinder<UUserWidget> LobbyMenuBPClass(TEXT("/game/MenuSystem/Blueprints/WBP_LobbyMenu"));
	if (!ensure(LobbyMenuBPClass.Class != nullptr)) return;
	LobbyMenuClass = LobbyMenuBPClass.Class;

	ConstructorHelpers::FClassFinder<UUserWidget> InGameMenuBPClass(TEXT("/game/MenuSystem/Blueprints/WBP_InGameMenu"));
	if (!ensure(InGameMenuBPClass.Class != nullptr)) return;
	InGameMenuClass = InGameMenuBPClass.Class;
}

void UCHGameInstance::Init()
{
	bIsTraveling = false;
	IOnlineSubsystem* SubSystem = IOnlineSubsystem::Get();
	if (SubSystem != nullptr)
	{
		SubSystem->OnConnectionStatusChangedDelegates.AddUObject(this, &UCHGameInstance::OnConnectionStatusChangedDelegates);

		if (*SubSystem->GetSubsystemName().ToString() == FString("NULL"))
		{
			bIsLan = true;
		}
		else
		{
			bIsLan = false;
		}

		UE_LOG(LogTemp, Warning, TEXT("Using subsystem %s"),*SubSystem->GetSubsystemName().ToString());

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
	if (!ensure(MainMenuClass != nullptr)) return;
	
	Menu = CreateWidget<UMainMenu>(this, MainMenuClass);
	if (!ensure(Menu != nullptr)) return;

	Menu->Setup();

	Menu->SetMenuInterface(this);

	FLevelStruct FirstLevel;
	FirstLevel.LevelImage = "/Game/MenuSystem/Images/Splash";
	FirstLevel.LevelName = "Example Map";
	FirstLevel.LevelPath = "/Game/FirstPersonCPP/Maps/FirstPersonExampleMap";

	TArray<FLevelStruct> LevelList;
	LevelList.Add(FirstLevel);

	Menu->SetLevelList(LevelList);
}

void UCHGameInstance::InLobbyLoadMenu()
{
	if (!ensure(LobbyMenuClass != nullptr)) return;

	LobbyMenu = CreateWidget<ULobbyMenu>(this, LobbyMenuClass);
	if (!ensure(LobbyMenu != nullptr)) return;

	LobbyMenu->Setup();

	LobbyMenu->SetMenuInterface(this);
}

void UCHGameInstance::InGameLoadMenu()
{
	if (!ensure(InGameMenuClass != nullptr)) return;

	UMenuWidget* Menu = CreateWidget<UMenuWidget>(this, InGameMenuClass);
	if (!ensure(Menu != nullptr)) return;

	Menu->Setup();

	Menu->SetMenuInterface(this);
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
	if (Menu != nullptr)
	{
		Menu->Teardown();
	}

	if (LobbyMenu != nullptr)
	{
		LobbyMenu->Teardown();
	}

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

void UCHGameInstance::AddPlayerToSquad(FPlayerData PlayerData)
{
	Squad.Add(PlayerData);
}

void UCHGameInstance::LoadMainMenu()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel("/Game/MenuSystem/MainMenu", ETravelType::TRAVEL_Absolute);
}

void UCHGameInstance::OnConnectionStatusChangedDelegates(const FString & ServiceName, EOnlineServerConnectionStatus::Type LastConnectionState, EOnlineServerConnectionStatus::Type ConnectionState)
{
	UE_LOG(LogTemp, Warning, TEXT("Service Name: %s"), *ServiceName);
	UE_LOG(LogTemp, Warning, TEXT("Last Connection State: %s"), LastConnectionState);
	UE_LOG(LogTemp, Warning, TEXT("Connection State: %s"), ConnectionState);
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
		
		if (Menu != nullptr)
		{
			Menu->Teardown();
		}

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
		if (!bIsTraveling && Menu != nullptr)
		{
			Menu->SetServerList(SearchResults);
		}
		
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

void UCHGameInstance::SetSingleplayerMap(FLevelStruct SelectedLevel)
{
	UE_LOG(LogTemp, Warning, TEXT("Setting single player level to: %s"), *SelectedLevel.LevelPath);
	SingleplayerLevel = SelectedLevel;
}

FLevelStruct UCHGameInstance::GetSingleplayerMap()
{
	return SingleplayerLevel;
}

void UCHGameInstance::SetMultiplayerMap(FLevelStruct SelectedLevel)
{
	MultiplayerLevel = SelectedLevel;
}

FLevelStruct UCHGameInstance::GetMultiplayerMap()
{
	return MultiplayerLevel;
}

void UCHGameInstance::LaunchSingleplayer()
{
	if (SingleplayerLevel.LevelPath != "")
	{
		if (Menu != nullptr)
		{
			Menu->Teardown();
		}

		UEngine* Engine = GetEngine();
		if (!ensure(Engine != nullptr)) return;


		UWorld* World = GetWorld();
		if (!ensure(World != nullptr)) return;
		bIsTraveling = true;
		World->ServerTravel(SingleplayerLevel.LevelPath);
	}
}

void UCHGameInstance::SetSquadSize(uint16 InSize)
{
	iSquadSize = InSize;
}

TArray<FPlayerData> UCHGameInstance::GetSquad()
{
	return Squad;
}

void UCHGameInstance::RefreshSquad()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	FPlayerData PlayerData;
	PlayerData.Username = PlayerController->PlayerState->GetPlayerName();
	PlayerData.Avatar = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *FString("/Game/MenuSystem/Images/avatar")));

	UE_LOG(LogTemp, Warning, TEXT("Adding player with username: %s"), *PlayerData.Username);

	AddPlayerToSquad(PlayerData);
}
