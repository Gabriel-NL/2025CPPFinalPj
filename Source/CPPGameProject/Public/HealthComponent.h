#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CPPGAMEPROJECT_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHealthComponent();

	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* ElectricalEffect;

	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* SmokeMediumEffect;

	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* SmokeHeavyEffect;

	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* SmallFireEffect;

	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* LargeFireEffect;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> GameOverWidgetClass;

	UPROPERTY()
	UUserWidget* GameOverWidget;

	UPROPERTY()
	UParticleSystemComponent* ActiveEffect = nullptr;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float DefaultHealth;

	UPROPERTY(BlueprintReadOnly)
	float Health;

	// Function to handle damage
	UFUNCTION()
	void TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCause);
};
