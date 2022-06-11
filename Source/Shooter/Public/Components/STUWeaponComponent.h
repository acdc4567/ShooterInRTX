// Ultimate Apex Shooter.All Rights Reserved..

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUWeaponComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTER_API USTUWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USTUWeaponComponent();



	void StartFire();
	void StopFire();




protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = Weapon)
		TSubclassOf<class ASTUBaseWeapon> WeaponClass;


	UPROPERTY(EditDefaultsOnly, Category = Weapon)
		FName WeaponAttachPointName = FName("RightHandSocket");

	


private:
	void SpawnWeapon();

	UPROPERTY()
		ASTUBaseWeapon* CurrentWeapon=nullptr;

	


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
