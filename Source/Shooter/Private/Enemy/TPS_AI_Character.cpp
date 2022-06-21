// Ultimate Apex Shooter.All Rights Reserved..


#include "Enemy/TPS_AI_Character.h"
#include "Blueprint/UserWidget.h"



// Sets default values
ATPS_AI_Character::ATPS_AI_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATPS_AI_Character::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;


}



// Called every frame
void ATPS_AI_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATPS_AI_Character::TakeDamage_Implementation(float Damage, float CriticalHitModifier, FHitResult HitResult) {
	if (!HitMarkerWidgetClass)return;

	bool bCritical;
	float Amt = SetDamage(Damage,50.f,CriticalHitModifier,HitResult,bCritical);
	bool bDead=0;
	UpdateHealth(Amt, bDead);
	bIsDeadx = bDead;

	if (bIsDeadx) {
		UE_LOG(LogTemp, Warning, TEXT("Dead "));
	}
	
	auto HitMarkerWidget = CreateWidget<UUserWidget>(GetWorld(), HitMarkerWidgetClass);
	if (HitMarkerWidget) {
		HitMarkerWidget->AddToViewport();
	}

}

float ATPS_AI_Character::SetDamage(float Damage, float CriticalHitChance, float CriticalHitModifier, const FHitResult& HitResult,bool& bWasCritical) {
	float RandomChance = FMath::RandRange(0.f, 100.f);
	float LocalDamageAmt = Damage;
	if (CriticalHitChance < RandomChance) {
		LocalDamageAmt *= CriticalHitModifier;
		bWasCritical = 1;
	}
	else {
		bWasCritical = 0;
	}


	return LocalDamageAmt;

}

void ATPS_AI_Character::UpdateHealth(float Damage, bool& bIsDead) {

	if (Damage >= CurrentHealth) {
		bIsDead = 1;
		CurrentHealth = 0;

	}
	else {
		CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.f, MaxHealth);
	}

	//UE_LOG(LogTemp, Warning, TEXT("CurrentHealth : %f "), CurrentHealth);

}

// Called to bind functionality to input
void ATPS_AI_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

