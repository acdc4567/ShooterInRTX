#pragma once

#include "TPS_Structs.generated.h"


class ATPS_BaseWeapon;


USTRUCT(BlueprintType)
struct FWeaponsData {
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Weapon)
		TSubclassOf<class ATPS_BaseWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Weapon)
		class UTexture2D* IconImage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Weapon)
		bool bIsEquipped;



};
