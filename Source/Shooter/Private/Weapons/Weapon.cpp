// Ultimate Apex Shooter.All Rights Reserved..


#include "Weapons/Weapon.h"

AWeapon::AWeapon() {

	PrimaryActorTick.bCanEverTick = 1;

}

void AWeapon::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (GetItemState() == EItemState::EIS_Falling&&bFalling) {
		const FRotator MeshRotation{ 0.f,GetItemMesh()->GetComponentRotation().Yaw,0.f };
		GetItemMesh()->SetWorldRotation(MeshRotation, 0, nullptr, ETeleportType::TeleportPhysics);;
	
	}



}

void AWeapon::ThrowWeapon() {

	FRotator MeshRotation{ 0.f,GetItemMesh()->GetComponentRotation().Yaw,0.f };
	GetItemMesh()->SetWorldRotation(MeshRotation,0,nullptr,ETeleportType::TeleportPhysics);
	const FVector MeshForward = GetItemMesh()->GetForwardVector();
	 const FVector MeshRight = GetItemMesh()->GetRightVector();
	 FVector ImpulseDirection = MeshRight.RotateAngleAxis(-20.f, MeshForward);
	 float RAndomRotation = FMath::RandRange(30.f, 60.f);
	 ImpulseDirection = ImpulseDirection.RotateAngleAxis(RAndomRotation, FVector(0.f, 0.f, 1.f));

	 ImpulseDirection *= ImpulseMultipler;
	 GetItemMesh()->AddImpulse(ImpulseDirection);

	 bFalling = 1;
	 GetWorldTimerManager().SetTimer(ThrowWeaponTimer, this, &AWeapon::StopFalling, ThrowWeaponTime);

}

void AWeapon::DecrementAmmo() {
	if (Ammo - 1 <= 0) {
		Ammo = 0;
	}
	else {
		--Ammo;
	}

}

void AWeapon::ReloadAmmo(int32 Amount) {

	checkf(Ammo + Amount <= MagazineCapacity, TEXT("TooManyBullets"));
	Ammo += Amount;



}

bool AWeapon::ClipIsFull() {


	return Ammo >= MagazineCapacity;;
}

void AWeapon::StopFalling() {

	bFalling = 0;
	SetItemState(EItemState::EIS_Pickup);




}
