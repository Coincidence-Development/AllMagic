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

	UFUNCTION(BlueprintCallable)
	void LoadMenu();

	UFUNCTION(Exec)
	void Host();

	UFUNCTION(Exec)
	void Join(const FString& Address);

private:
	TSubclassOf<class UUserWidget> MenuClass;

	class UMainMenu* Menu;
};
