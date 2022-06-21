// Ultimate Apex Shooter.All Rights Reserved..


#include "Character/TPS_Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Weapons/TPS_BaseWeapon.h"
#include "Animation/AnimMontage.h"
#include "WeaponBuys/WeaponBuyBase.h"

DEFINE_LOG_CATEGORY_STATIC(BaseCharacterLog, All, All);



// Sets default values
ATPS_Character::ATPS_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SocketOffset = FVector(0.f, 80.f, 80.f);
	SpringArmComponent->SetupAttachment(GetRootComponent());

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);





}

// Called when the game starts or when spawned
void ATPS_Character::BeginPlay()
{
	Super::BeginPlay();
	
	OneKeyPressed();






}

void ATPS_Character::TurnAround(float Value) {

	AddControllerYawInput(Value * MouseHipTurnRate);

}

void ATPS_Character::LookUp(float Value) {

	AddControllerPitchInput(Value * MouseHipLookUpRate);

}

void ATPS_Character::MoveForward(float Value) {
	if (Value == 0.f)return;
	AddMovementInput(GetActorForwardVector(), Value);




}

void ATPS_Character::MoveRight(float Value) {

	if (Value == 0.f)return;
	AddMovementInput(GetActorRightVector(), Value);



}

void ATPS_Character::EquipWeapon(ATPS_BaseWeapon* Weapon) {
	if (!Weapon)return;

	if (!bIsChangingWeapon) {
	
		bIsChangingWeapon = 1;
		ShowWeapon(Weapon);
		CurrentWeapon = Weapon;
		HasWeaponEnum = EHasWeapon::EHW_HasWeapon;
		




	}









}

void ATPS_Character::ShowWeapon(ATPS_BaseWeapon* WeaponToShow) {

	WeaponSlot_01 = WeaponToShow;
	WeaponSlot_01->SetActorHiddenInGame(0);


}

ATPS_BaseWeapon* ATPS_Character::SpawnWeapon(TSubclassOf<ATPS_BaseWeapon> WeaponClass) {
	if (!WeaponClass)return nullptr;

	const FTransform SpawnTransform( GetActorTransform());
	ATPS_BaseWeapon* SpawnedWeapon = GetWorld()->SpawnActor<ATPS_BaseWeapon>(WeaponClass, SpawnTransform);
	if (SpawnedWeapon) {
		WeaponSlot_01 = SpawnedWeapon;
		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, 0);

		WeaponSlot_01->AttachToComponent(GetMesh(), AttachmentRules,WeaponSlot_01->GetSocketName());
	
		CurrentWeapon = WeaponSlot_01;
		HasWeaponEnum = EHasWeapon::EHW_HasWeapon;
		SpawnedWeapon->SetOwner(this);
		return SpawnedWeapon;
	}
	
	return nullptr;

}

void ATPS_Character::OneKeyPressed() {

	EquipWeapon(SpawnWeapon(DefaultWeaponClass));

}

void ATPS_Character::StartFire() {
	if (!CurrentWeapon) {
		return;

	}
	bIsFiring = 1;
	PlayGunFireMontage();
	CurrentWeapon->StartFire();

}

void ATPS_Character::StopFire() {
	if (!CurrentWeapon) {
		return;

	}
	bIsFiring = 0;
	CurrentWeapon->StopFire();
}

void ATPS_Character::SelectButtonPressed() {

	if (ItemNearby) {
		DropWeapon();
		EquipWeapon(SpawnWeapon(ItemNearby->GetWeaponClass()));

	}
}



void ATPS_Character::DropWeapon() {
	if (CurrentWeapon) {
		FDetachmentTransformRules DetachmentTransformRules(EDetachmentRule::KeepWorld, 1);
		CurrentWeapon->GetGunMesh()->DetachFromComponent(DetachmentTransformRules);
		CurrentWeapon->SetLifeSpan(1.f);
	}



}




// Called every frame
void ATPS_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}








// Called to bind functionality to input
void ATPS_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &ATPS_Character::TurnAround);
	PlayerInputComponent->BindAxis("LookUp", this, &ATPS_Character::LookUp);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATPS_Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATPS_Character::MoveRight);

	PlayerInputComponent->BindAction("Jump",IE_Pressed, this, &ATPS_Character::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ATPS_Character::StopJumping);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ATPS_Character::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &ATPS_Character::StopFire);

	PlayerInputComponent->BindAction("Select", IE_Pressed, this, &ATPS_Character::SelectButtonPressed);
	




}

float ATPS_Character::GetMovementDirection() const {
	if (GetVelocity().IsZero())return 0.f;
	const auto VelocityNormal = GetVelocity().GetSafeNormal();
	const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
	const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
	const auto Degrees = FMath::RadiansToDegrees(AngleBetween);

	return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);

}

EWeaponxTypes ATPS_Character::GetCurrentWeaponType() const {

	if (CurrentWeapon) {
		return CurrentWeapon->GetWeaponType();
	}
	return EWeaponxTypes::EWXT_MAX;
}




bool ATPS_Character::GetIsFiring() const {
	return bIsFiring;
}




void ATPS_Character::PlayGunFireMontage() {

	PlayAnimMontage(HipFireMontage);

}

void ATPS_Character::IncrementOverlappedItemCount(AWeaponBuyBase* WeaponBuy) {
	if (WeaponBuy) {
		ItemNearby = WeaponBuy;
	}
	else {
		ItemNearby = nullptr;
	}

}

