#include "HealthComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"  

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = false;

    DefaultHealth = 200;
    Health = DefaultHealth;

    // Assign the GameOverWidgetClass programmatically if not done via Editor
    static ConstructorHelpers::FClassFinder<UUserWidget> GameOverWidgetClassFinder(TEXT("/Game/UI/WB_GameOver"));
    if (GameOverWidgetClassFinder.Succeeded())
    {
        GameOverWidgetClass = GameOverWidgetClassFinder.Class;
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to find WB_GameOver widget class"));
    }
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

    // Handle damage effects, ensuring only one effect is active at a time
    if (Health <= 180 && Health > 140)
    {
        // Destroy the previously active effect if any
        if (ActiveEffect && ActiveEffect->Template != ElectricalEffect)
        {
            ActiveEffect->DestroyComponent();
        }

        if (!ActiveEffect && ElectricalEffect)
        {
            ActiveEffect = UGameplayStatics::SpawnEmitterAttached(ElectricalEffect, CarRoot);
            ActiveEffect->SetWorldScale3D(LargeScale);
        }
    }
    else if (Health <= 140 && Health > 100)
    {
        // Destroy the previously active effect if any
        if (ActiveEffect && ActiveEffect->Template != SmokeMediumEffect)
        {
            ActiveEffect->DestroyComponent();
        }

        if (!ActiveEffect && SmokeMediumEffect)
        {
            ActiveEffect = UGameplayStatics::SpawnEmitterAttached(SmokeMediumEffect, CarRoot);
            ActiveEffect->SetWorldScale3D(LargeScale);
        }
    }
    else if (Health <= 100 && Health > 80)
    {
        // Destroy the previously active effect if any
        if (ActiveEffect && ActiveEffect->Template != SmokeHeavyEffect)
        {
            ActiveEffect->DestroyComponent();
        }

        if (!ActiveEffect && SmokeHeavyEffect)
        {
            ActiveEffect = UGameplayStatics::SpawnEmitterAttached(SmokeHeavyEffect, CarRoot);
            ActiveEffect->SetWorldScale3D(LargeScale);
        }
    }
    else if (Health <= 80 && Health > 30)
    {
        // Destroy the previously active effect if any
        if (ActiveEffect && ActiveEffect->Template != SmallFireEffect)
        {
            ActiveEffect->DestroyComponent();
        }

        if (!ActiveEffect && SmallFireEffect)
        {
            ActiveEffect = UGameplayStatics::SpawnEmitterAttached(SmallFireEffect, CarRoot);
            ActiveEffect->SetWorldScale3D(LargeScale);
        }
    }
    else if (Health <= 30 && Health > 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("Car low!"));

        // Destroy the previously active effect if any
        if (ActiveEffect && ActiveEffect->Template != LargeFireEffect)
        {
            ActiveEffect->DestroyComponent();
        }

        if (!ActiveEffect && LargeFireEffect)
        {
            ActiveEffect = UGameplayStatics::SpawnEmitterAttached(LargeFireEffect, CarRoot);
            ActiveEffect->SetWorldScale3D(LargeScale);
        }
    }

    //// When health reaches zero, show the GameOver widget
    else if (Health <= 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("Car at 0!"));

        APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
            // Create the widget using WB_GameOver
            GameOverWidget = CreateWidget<UUserWidget>(PlayerController, GameOverWidgetClass);
            GameOverWidget->AddToViewport(); // Show widget on screen
                PlayerController->SetShowMouseCursor(true); // Optional: Enable cursor for UI interaction

    }
}


