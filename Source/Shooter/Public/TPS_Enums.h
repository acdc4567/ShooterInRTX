#pragma once


DECLARE_MULTICAST_DELEGATE_OneParam(FOnInteract,bool);







UENUM(BlueprintType)
enum class EWeaponxTypes :uint8 {
	EWXT_Pistol UMETA(DisplayName = "Pistol")
	, EWXT_AssaultRifle UMETA(DisplayName = "Assault Rifle")
	, EWXT_Shotgun UMETA(DisplayName = "Shotgun")
	, EWXT_GrenadeLauncher UMETA(DisplayName = "Grenade Launcher")
	, EWXT_RocketLauncher UMETA(DisplayName = "Rocket Launcher")
	, EWXT_SniperRifle UMETA(DisplayName = "Sniper Rifle")
	, EWXT_MAX UMETA(DisplayName = "DefaultMAX")

};

UENUM(BlueprintType)
enum class EHasWeapon :uint8 {
	EHW_NoWeapon UMETA(DisplayName = "No Weapon")
	, EHW_HasWeapon UMETA(DisplayName = "Has Weapon")
	
	, EHW_MAX UMETA(DisplayName = "DefaultMAX")

};


