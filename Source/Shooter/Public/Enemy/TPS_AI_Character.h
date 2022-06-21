// Ultimate Apex Shooter.All Rights Reserved..

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/TakeDamage.h"
#include "TPS_AI_Character.generated.h"

UCLASS()
class SHOOTER_API ATPS_AI_Character : public ACharacter,public ITakeDamage
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATPS_AI_Character();



	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = AI)
		class UBehaviorTree* BehaviorTreeAsset;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		float CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
		float MaxHealth=100.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		bool bIsDeadx=0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Movement)
		TSubclassOf<class UUserWidget> HitMarkerWidgetClass;

	
	//Functions

	float SetDamage(float Damage, float CriticalHitChance, float CriticalHitModifier, const FHitResult& HitResult, bool& bWasCritical);

	void UpdateHealth(float Damage,bool& bIsDead);








public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	virtual void TakeDamage_Implementation(float Damage, float CriticalHitModifier, FHitResult HitResult) override;
	


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
