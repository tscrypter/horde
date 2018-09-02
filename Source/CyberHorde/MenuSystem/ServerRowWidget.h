// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ServerRowWidget.generated.h"

/**
 * 
 */
UCLASS()
class CYBERHORDE_API UServerRowWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ServerName;

	UPROPERTY(BluePrintReadOnly)
	bool bIsSelected = false;

	void Setup(class UMainMenu* InParent, FString InSessionIdStr);

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* RowButton;

	UPROPERTY()
	UMainMenu * Parent;

	FString SessionIdStr;

	UFUNCTION()
	void OnClicked();
	
};
