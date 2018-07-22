// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"
#include "AllMagicGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ALLMAGIC_API UAllMagicGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()

public:
	UAllMagicGameInstance(const FObjectInitializer & ObjectInitializer);

	virtual void Init();

	virtual void LoadMainMenu() override;

	UFUNCTION(BlueprintCallable)
	void LoadMenu();

	UFUNCTION(BlueprintCallable)
	void LoadInGameMenu();

	UFUNCTION(Exec)
	void Host() override;

	UFUNCTION(Exec)
	void Join(const FString& Address) override;

private:
	TSubclassOf<class UUserWidget> MenuClass;
	TSubclassOf<class UUserWidget> InGameMenuClass;

	class UMainMenu* Menu;
};
