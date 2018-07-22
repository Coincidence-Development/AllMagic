// Fill out your copyright notice in the Description page of Project Settings.

#include "InGameMenu.h"

#include "Components/Button.h"


bool UInGameMenu::Initialize()
{
	if (!Super::Initialize()) return false;

	if (!ensure(CancelButton != nullptr)) return false;
	CancelButton->OnClicked.AddDynamic(this, &UInGameMenu::CancelPressed);

	if (!ensure(QuitButton != nullptr)) return false;
	QuitButton->OnClicked.AddDynamic(this, &UInGameMenu::QuitPressed);

	return true;
}

void UInGameMenu::CancelPressed()
{
	RemoveFromParent();
}

void UInGameMenu::QuitPressed()
{
	if (MenuInterface != nullptr)
	{
		RemoveFromParent();
		MenuInterface->LoadMainMenu();
	}
}
