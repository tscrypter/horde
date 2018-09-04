// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerGrid.h"

#include "Engine/Texture2D.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/PanelWidget.h"

#include "PlayerCard.h"

UPlayerGrid::UPlayerGrid(const FObjectInitializer & ObjectInitializer) :Super(ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> PlayerCardBPClass(TEXT("/Game/MenuSystem/Blueprints/WBP_PlayerCard"));
	if (!ensure(PlayerCardBPClass.Class != nullptr)) return;

	PlayerCardClass = PlayerCardBPClass.Class;
}

void UPlayerGrid::AddPlayer(FString Username, UTexture2D* Avatar)
{
	FPlayerData PlayerData;
	PlayerData.Avatar = Avatar;
	PlayerData.Username = Username;
	Players.Add(PlayerData);
	AddPlayerCardToGrid(PlayerData);
}

void UPlayerGrid::AddPlayer(FString Username, FString AvatarPath)
{
	FPlayerData PlayerData;
	PlayerData.Username = Username;
	UTexture2D* Texture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *AvatarPath));
	PlayerData.Avatar = Texture;
	Players.Add(PlayerData);
	AddPlayerCardToGrid(PlayerData);
}

void UPlayerGrid::AddPlayer(FPlayerData PlayerData)
{
	if (!ensure(PlayerData.Avatar != nullptr)) return;
	if (!ensure(!PlayerData.Username.IsEmpty())) return;

	Players.Add(PlayerData);
	AddPlayerCardToGrid(PlayerData);
}

FPlayerData UPlayerGrid::GetPlayerData(FString Username)
{
	for (FPlayerData PlayerData : Players)
	{
		if (PlayerData.Username == Username)
		{
			return PlayerData;
		}
	}
	return FPlayerData();
}

void UPlayerGrid::AddPlayerCardToGrid(FPlayerData PlayerData)
{
	UWorld* World = this->GetWorld();
	if (!ensure(World != nullptr)) return;

	UPlayerCard* PlayerCard = CreateWidget<UPlayerCard>(World, PlayerCardClass);
	
	PlayerCard->SetPlayer(PlayerData);
	PlayerCards->AddChild(PlayerCard);
}

void UPlayerGrid::RemovePlayer(FString Username)
{
	auto PlayerData = GetPlayerData(Username);
	if (PlayerData.Username != Username) return;
//	Players.Remove(PlayerData);
}
