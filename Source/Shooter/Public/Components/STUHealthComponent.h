// Ultimate Apex Shooter.All Rights Reserved..

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTER_API USTUHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USTUHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	float MaxHealth = 100.f;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Heal)
		bool bAutoHeal = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Heal)
		float HealUpdateTime = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Heal)
		float HealDelay = 3.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Heal)
		float HealModifier = 5.f;


private:
	float Health = 0.f;

	UFUNCTION()
		void OnTakeAnyDamageHandle(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	

	FTimerHandle HealTimerHandle;

	void HealUpdate();

	void SetHealth(float NewHealth);





public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	float GetHealth() const { return Health; }


	UFUNCTION(BlueprintCallable) 
		bool IsDead() const { return FMath::IsNearlyZero(Health); }

	FOnDeath OnDeath;
	FOnHealthChanged OnHealthChanged;






};
