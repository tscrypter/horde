// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "../CHStructs.h"

#include "PlayerGrid.generated.h"

/**
 * 
 */
UCLASS()
class CYBERHORDE_API UPlayerGrid : public UUserWidget
{
	GENERATED_BODY()

public:
	UPlayerGrid(const FObjectInitializer & ObjectInitializer);

	void AddPlayer(FString Username, UTexture2D* Avatar);
	void AddPlayer(FString Username, FString AvatarPath);
	void AddPlayer(FPlayerData PlayerData);
	void RemovePlayer(FString Username);

private:
	TSubclassOf<class UUserWidget> PlayerCardClass;

	TArray<FPlayerData> Players;

	UPROPERTY(meta = (BindWidget))
	class UPanelWidget* PlayerCards;

	FPlayerData GetPlayerData(FString Username);
	void AddPlayerCardToGrid(FPlayerData PlayerData);
	
	
};
