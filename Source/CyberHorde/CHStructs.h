// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Texture2D.h"

#include "CHStructs.generated.h"

USTRUCT()
struct FLevelStruct
{
	GENERATED_BODY()

	FString LevelName;
	FString LevelPath;
	FString LevelImage;
};

USTRUCT()
struct FServerData
{
	GENERATED_BODY()

	FString Name;
	uint16 CurrentPlayers;
	uint16 MaxPlayers;
	FString HostUsername;
};

USTRUCT()
struct FPlayerData
{
	GENERATED_BODY()

	FString Username;
	UTexture2D* Avatar;
};