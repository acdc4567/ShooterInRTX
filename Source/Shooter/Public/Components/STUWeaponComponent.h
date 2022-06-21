// Ultimate Apex Shooter.All Rights Reserved..

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUCoreTypes.h"
#include "STUWeaponComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTER_API USTUWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USTUWeaponComponent();



	virtual void StartFire();
	void StopFire();

	virtual void NextWeapon();
	void Reload();



protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;



	UPROPERTY(EditDefaultsOnly, Category = Weapon)
		TArray< FWeaponData> WeaponData;


	UPROPERTY(EditDefaultsOnly, Category = Weapon)
		FName WeaponEquipSocketName = FName("RightHandSocket");

	UPROPERTY(EditDefaultsOnly, Category = Weapon)
		FName WeaponArmorySocketName = FName("ArmorySocket");

	UPROPERTY(EditDefaultsOnly, Category = Weapon)
		UAnimMontage* EquipAnimMontage ;

	UPROPERTY()
		ASTUBaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY()
		TArray< ASTUBaseWeapon*> Weapons;

	bool CanFire() const;
	bool CanEquip() const;

	void EquipWeapon(int32 WeaponIndex);

	int32 CurrentWeaponIndex = 0;


private:
	void SpawnWeapons();

	

	UPROPERTY()
		UAnimMontage* CurrentReloadAnimMontage=nullptr;
	

	
	void AttachWeaponToSocket(ASTUBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);

	
	void PlayAnimMontage(UAnimMontage* Animation);

	void InitAnimations();
	void OnEquipFinished(USkeletalMeshComponent* MeshComp);
	void OnReloadFinished(USkeletalMeshComponent* MeshComp);

	bool bEquipAnimInProgress=0;
	bool bReloadAnimInProgress = 0;

	
	bool CanReload() const;

	void OnEmptyClip();
	void ChangeClip();

	







public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
