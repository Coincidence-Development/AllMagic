// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class ALLMAGIC_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual bool Initialize() override;

public:
	void SetMenuInterface(IMenuInterface* MenuInterface);

	void Setup();
	void RemoveFromParent() override;

private:
	UFUNCTION()
	void HostServer();

	IMenuInterface* MenuInterface;

	APlayerController* PlayerController;

	UPROPERTY(meta = (BindWidget))
	class UButton* HostButton;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* JoinMenuButton;
};
