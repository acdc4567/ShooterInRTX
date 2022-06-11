// Ultimate Apex Shooter.All Rights Reserved..


#include "Components/STUWeaponComponent.h"
#include "Weapons/STUBaseWeapon.h"
#include "GameFramework/Character.h"





// Sets default values for this component's properties
USTUWeaponComponent::USTUWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}



void USTUWeaponComponent::StartFire() {
	if (!CurrentWeapon)return;
	CurrentWeapon->StartFire();


}

void USTUWeaponComponent::StopFire() {

	if (!CurrentWeapon)return;
	CurrentWeapon->StopFire();


}
// Called when the game starts
void USTUWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	SpawnWeapon();
	// ...
	
}


// Called every frame
void USTUWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USTUWeaponComponent::SpawnWeapon() {

	if (!GetWorld())return;

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;
	CurrentWeapon = GetWorld()->SpawnActor<ASTUBaseWeapon>(WeaponClass);
	if (!CurrentWeapon) return;

	
	

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, 0);
	CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponAttachPointName);
	CurrentWeapon->SetOwner(GetOwner());

	


}