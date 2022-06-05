// Ultimate Apex Shooter.All Rights Reserved..

#pragma once

#include "CoreMinimal.h"
#include "Weapons/Item.h"
#include "AmmoTypes.h"
#include "Weapon.generated.h"



UENUM(BlueprintType)
enum class EWeaponType :uint8 {
	EWT_SubmachineGun UMETA(DisplayName = "SubmachineGun")
	, EWT_AssaultRifle UMETA(DisplayName = "AssaultRifle")
	
	, EWT_MAX UMETA(DisplayName = "DefaultMAX")

};

/**
 * 
 */
UCLASS()
class SHOOTER_API AWeapon : public AItem
{
	GENERATED_BODY()
	
public:

	AWeapon();

	virtual void Tick(float DeltaTime) override;

protected:
	

	void StopFalling();

	
private:

	FTimerHandle ThrowWeaponTimer;
	float ThrowWeaponTime=0.7f;
	bool bFalling=0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ItemProperties, meta = (AllowPrivateAccess = "true"))
		float ImpulseMultipler = 2000.f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponProperties, meta = (AllowPrivateAccess = "true"))
		int32 Ammo=30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponProperties, meta = (AllowPrivateAccess = "true"))
		int32 MagazineCapacity = 30;




	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponProperties, meta = (AllowPrivateAccess = "true"))
		FName TwinPistolBoneName = FName(TEXT("Bonex2"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponProperties, meta = (AllowPrivateAccess = "true"))
		EWeaponType WeaponType=EWeaponType::EWT_SubmachineGun;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponProperties, meta = (AllowPrivateAccess = "true"))
		EAmmoType AmmoType = EAmmoType::EAT_9mm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponProperties, meta = (AllowPrivateAccess = "true"))
		FName ReloadMontageSection = FName(TEXT("ReloadSMG"));

public:

		void ThrowWeapon();

		FORCEINLINE int32 GetAmmo() const { return Ammo; }
		FORCEINLINE int32 GetMagazineCapacity() const { return MagazineCapacity; }

		void DecrementAmmo();

		FORCEINLINE FName GetTwinPistolBoneName() const { return TwinPistolBoneName; }

		FORCEINLINE EWeaponType GetWeaponType() const { return WeaponType; }

		FORCEINLINE EAmmoType GetAmmoType() const { return AmmoType; }

		FORCEINLINE FName GetReloadMontageSectionName() const { return ReloadMontageSection; }

		void ReloadAmmo(int32 Amount);

		bool ClipIsFull();


};
