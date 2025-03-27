// Fill out your copyright notice in the Description page of Project Settings.

#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	DefaultHealth = 200;
	Health = DefaultHealth;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	if (Owner)
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
	}

}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCause)
{
    USceneComponent* CarRoot = GetOwner()->GetRootComponent(); // Get car's root

	if (Damage <= 0)
	{
        UE_LOG(LogTemp, Warning, TEXT("Car Destroyed!"));
		return;
	}
    Health = FMath::Clamp(Health - Damage, 0.0f, DefaultHealth);

    if (!CarRoot) return;

    FVector LargeScale = FVector(3.0f, 3.0f, 3.0f);  // Adjust as needed

    if (Health <= 180 && Health > 140)
    {
        ActiveEffect = UGameplayStatics::SpawnEmitterAttached(ElectricalEffect, CarRoot);
        ActiveEffect->SetWorldScale3D(LargeScale);
    }
    else if (Health <= 140 && Health > 100)
    {
        ActiveEffect = UGameplayStatics::SpawnEmitterAttached(SmokeMediumEffect, CarRoot);
        ActiveEffect->SetWorldScale3D(LargeScale);
    }
    else if (Health <= 100 && Health > 80)
    {
        ActiveEffect = UGameplayStatics::SpawnEmitterAttached(SmokeHeavyEffect, CarRoot);
        ActiveEffect->SetWorldScale3D(LargeScale);
    }
    else if (Health <= 80 && Health > 30)
    {
        ActiveEffect = UGameplayStatics::SpawnEmitterAttached(SmallFireEffect, CarRoot);
        ActiveEffect->SetWorldScale3D(LargeScale);
    }
    else if (Health <= 30 && Health > 0)
    {
        ActiveEffect = UGameplayStatics::SpawnEmitterAttached(LargeFireEffect, CarRoot);
        ActiveEffect->SetWorldScale3D(LargeScale);
    }
	//UE_LOG(LogTemp, Warning, TEXT("Health Updated: %f"), Health);
}



