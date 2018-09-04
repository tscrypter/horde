// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "../CHStructs.h"

#include "PlayerCard.generated.h"

/**
 * 
 */
UCLASS()
class CYBERHORDE_API UPlayerCard : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void SetPlayer(FPlayerData PlayerData);
	

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* UsernameTextBlock;	// Display username of player

	UPROPERTY(meta = (BindWidget))
	class UImage* AvatarImage;			// Display the Avatar of the player
	
};
