// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Components/HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TimerManager.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	//Component Setable Defaults
	bIsKillable = true;
	DefaultHealth = 100;

	//Local variables for event handeling
	bIsDead = false;
	CurrentHealth = DefaultHealth;
	TimerCount = 0;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = DefaultHealth;

	AActor* MyOwner = GetOwner();
	if (MyOwner)
	{
		MyOwner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::HandleTakeAnyDamage);
	}	
}

void UHealthComponent::HandleTakeAnyDamage(AActor * DamageActor, float Damage, const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser)
{
	if (Damage <= 0 || bIsDead) { return; }
	
	CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.0f, DefaultHealth);

	//TODO: Remove UE_LOG
	UE_LOG(LogTemp, Warning, TEXT("Health Changed: %s"), *FString::SanitizeFloat(CurrentHealth))

	if (CurrentHealth <= 0) { bIsDead = true; };

	OnHealthUpdate.Broadcast(CurrentHealth, bIsDead);
}

void UHealthComponent::Heal(float HealAmount, float TimeInSeconds)
{
	if (bIsDead) { return; }
	DeltaHealth = HealAmount / TimeInSeconds / TimerTickPerSecond;
	TimerTotalCount = TimeInSeconds * TimerTickPerSecond;

	GetWorld()->GetTimerManager().SetTimer(TimerHandle_DeltaHealth, this, &UHealthComponent::ChangeHealth, 1 / TimerTickPerSecond, true, 0.0f);

	//TODO: Remove UE_Log
	UE_LOG(LogTemp, Warning, TEXT("%s Health Changed: %s (+%s)"), *FString(GetOwner()->GetName()), *FString::SanitizeFloat(CurrentHealth), *FString::SanitizeFloat(HealAmount)); //TODO: Remove UE_LOG after confirmed working condition

	OnHealthUpdate.Broadcast(CurrentHealth, bIsDead);

}

void UHealthComponent::ChangeHealth()
{
	TimerCount++;
	CurrentHealth = CurrentHealth + DeltaHealth;

	if (CurrentHealth >= DefaultHealth)
	{
		CurrentHealth = DefaultHealth;
	}

	if (TimerCount >= TimerTotalCount || CurrentHealth == DefaultHealth)
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_DeltaHealth);
		TimerCount = 0;
	}
}

