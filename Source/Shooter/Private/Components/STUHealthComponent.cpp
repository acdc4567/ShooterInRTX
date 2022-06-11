// Ultimate Apex Shooter.All Rights Reserved..


#include "Components/STUHealthComponent.h"
#include "GameFramework/Actor.h"
#include "Dev/STUFireDamageType.h"
#include "Dev/STUIceDamageType.h"
#include "Engine/World.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY_STATIC(HealthComponentLog, All, All);


// Sets default values for this component's properties
USTUHealthComponent::USTUHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = 1;

	// ...
}


// Called when the game starts
void USTUHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	SetHealth(MaxHealth);
	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner) {
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamageHandle);

	}

	
}


void USTUHealthComponent::HealUpdate() {

	SetHealth(Health + HealModifier);

	if ( FMath::IsNearlyEqual(Health,MaxHealth) && GetWorld()) {
		GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	}

}

void USTUHealthComponent::SetHealth(float NewHealth) {

	Health = FMath::Clamp(NewHealth, 0.f, MaxHealth);
	OnHealthChanged.Broadcast(Health);


}

// Called every frame
void USTUHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USTUHealthComponent::OnTakeAnyDamageHandle(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser) {

	if (Damage <= 0.f || IsDead()||!GetWorld())return;
	SetHealth(Health - Damage);
	GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);

	
	
	if (IsDead()) {
		OnDeath.Broadcast();
	}
	else if (bAutoHeal&&GetWorld()) {
		GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &USTUHealthComponent::HealUpdate, HealUpdateTime,1,HealDelay);
	}
	

}