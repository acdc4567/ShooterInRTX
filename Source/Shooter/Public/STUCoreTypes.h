#pragma once

#include "STUCoreTypes.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnClipEmptySignature);

//Base Weapon

class ASTUBaseWeapon;

USTRUCT(BlueprintType)
struct FAmmoData {
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Weapon)
		int32 Bullets;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Weapon, meta = (EditCondition = "!bInfinite"))
		int32 Clips;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Weapon)
		bool bInfinite;

};



USTRUCT(BlueprintType)
struct FWeaponData {
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Weapon)
		TSubclassOf<class ASTUBaseWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Weapon)
		UAnimMontage* ReloadAnimMontage;



};


//Health Component
DECLARE_MULTICAST_DELEGATE(FOnDeath);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float);

