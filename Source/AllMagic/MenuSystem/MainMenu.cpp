// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"

#include "Components/Button.h"

bool UMainMenu::Initialize()
{
	if (!Super::Initialize()) return false;

	if (!ensure(HostButton != nullptr)) return false;
	HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);


	Setup();
	return true;
}

void UMainMenu::SetMenuInterface(IMenuInterface* MenuInterface)
{
	this->MenuInterface = MenuInterface;
}

void UMainMenu::Setup()
{
	this->AddToViewport();

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(this->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = true;
}

//Override method, change the input mode to game only and hides the mouse cursor
void UMainMenu::RemoveFromParent()
{
	Super::RemoveFromParent();

	FInputModeGameOnly InputModeData;

	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = false;
}

void UMainMenu::HostServer()
{
	if (MenuInterface != nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Hosting Server!"));
		MenuInterface->Host();
	}
}