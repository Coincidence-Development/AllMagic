// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthUpdatedSignature, float, Health, bool, bHasDied);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ALLMAGIC_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void HandleTakeAnyDamage(AActor* DamageActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);


public:
	//This will heal the players health over specified time
	//HealAmount is total heath to gain
	//TimeInSeconds is duration
	UFUNCTION(BlueprintCallable, Category = "HealthComponent")
		void Heal(float HealAmount, float TimeInSeconds);



	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnHealthUpdatedSignature OnHealthUpdate;


private:
	void ChangeHealth();

	//Owners starting health
	UPROPERTY(EditDefaultsOnly, Category = "Variable")
	float DefaultHealth;

	//Can the Owner be killed COMPLETELY?
	//Owner will be removed from world if this is true
	//Owner will respawn after event or time if this is false
	UPROPERTY(EditDefaultsOnly, Category = "Variable")
	bool bIsKillable;

	//Local Variables


	UPROPERTY(VisibleAnywhere, Category = "Current Values")
	bool bIsDead;
	FTimerHandle TimerHandle_DeltaHealth;
	float TimerTickPerSecond = 3;

	float DeltaHealth;		//Health change per timer tick
	uint8 TimerTotalCount;	//Totle Ticks of the timer
	uint8 TimerCount;		//Current Timer Tick

	UPROPERTY(VisibleAnywhere, Category = "Current Values")
	uint16 CurrentHealth;

};
