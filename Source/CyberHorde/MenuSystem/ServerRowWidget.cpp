// Fill out your copyright notice in the Description page of Project Settings.

#include "ServerRowWidget.h"
#include "Components/Button.h"
#include "MainMenu.h"

void UServerRowWidget::Setup(UMainMenu * InParent, FString InSessionIdStr)
{
	Parent = InParent;
	SessionIdStr = InSessionIdStr;
	RowButton->OnClicked.AddDynamic(this, &UServerRowWidget::OnClicked);
}

void UServerRowWidget::OnClicked()
{
	Parent->SelectServer(SessionIdStr);
}
