// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCard.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UPlayerCard::SetPlayer(FPlayerData PlayerData)
{
	UsernameTextBlock->SetText(FText::FromString(PlayerData.Username));
	AvatarImage->SetBrushFromTexture(PlayerData.Avatar);
}


