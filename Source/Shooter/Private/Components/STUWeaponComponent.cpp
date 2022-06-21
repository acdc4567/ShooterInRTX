// Ultimate Apex Shooter.All Rights Reserved..


#include "Components/STUWeaponComponent.h"
#include "Weapons/STUBaseWeapon.h"
#include "GameFramework/Character.h"
#include "Animation/STUEquipFinishedAnimNotify.h"
#include "Animation/STUReloadAnimNotify.h"
#include "Animation/AnimUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All);

constexpr static int32 WeaponsNum = 2;

// Sets default values for this component's properties
USTUWeaponComponent::USTUWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}



void USTUWeaponComponent::StartFire() {
	if (!CanFire())return;
	CurrentWeapon->StartFire();


}

void USTUWeaponComponent::StopFire() {

	if (!CurrentWeapon)return;
	CurrentWeapon->StopFire();


}


void USTUWeaponComponent::NextWeapon() {

	if (!CanEquip())return;
	CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	EquipWeapon(CurrentWeaponIndex);



}

void USTUWeaponComponent::Reload() {
	ChangeClip();

}





// Called when the game starts
void USTUWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	checkf(WeaponData.Num() == WeaponsNum, TEXT("Choose %i Weapons"),WeaponsNum);

	CurrentWeaponIndex = 0;
	InitAnimations();
	SpawnWeapons();
	EquipWeapon(CurrentWeaponIndex);
	



	// ...
	



}

void USTUWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason) {

	CurrentWeapon = nullptr;
	for (auto Weapon : Weapons) {
		Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Weapon->Destroy();


	}
	Weapons.Empty();
	Super::EndPlay(EndPlayReason);


}




// Called every frame
void USTUWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}



void USTUWeaponComponent::SpawnWeapons() {

	

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character||!GetWorld()) return;

	for (auto OneWeaponData : WeaponData) {

		auto Weapon=GetWorld()->SpawnActor<ASTUBaseWeapon>(OneWeaponData.WeaponClass );
		if (!Weapon)continue;
		Weapon->OnClipEmpty.AddUObject(this, &USTUWeaponComponent::OnEmptyClip);
		Weapon->SetOwner(GetOwner());

		Weapons.Add(Weapon);
		AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
		
	}




}


void USTUWeaponComponent::AttachWeaponToSocket(ASTUBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName) {
	if (!Weapon || !SceneComponent)return;

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, 0);
	Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);





}

void USTUWeaponComponent::EquipWeapon(int32 WeaponIndex) {

	if (WeaponIndex < 0 || WeaponIndex >= Weapons.Num()) {
		UE_LOG(LogWeaponComponent, Warning, TEXT("InvalidWeaponIndex"));
		return;
	}

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character ) return;

	if (CurrentWeapon) {
		CurrentWeapon->StopFire();

		AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);

	}


	CurrentWeapon = Weapons[WeaponIndex];

	const auto CurrentWeaponData = WeaponData.FindByPredicate([&](const FWeaponData& Data) { return Data.WeaponClass == CurrentWeapon->GetClass(); });

	CurrentReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage : nullptr;
	AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
	bEquipAnimInProgress = 1;
	
	PlayAnimMontage(EquipAnimMontage);

}

void USTUWeaponComponent::PlayAnimMontage(UAnimMontage* Animation) {

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;


	Character->PlayAnimMontage(Animation);



}

void USTUWeaponComponent::InitAnimations() {

	

	auto EquipFinishedNotify = AnimUtils::FindNotifyByClass<USTUEquipFinishedAnimNotify>(EquipAnimMontage);
	if (EquipFinishedNotify) {

		EquipFinishedNotify->OnNotified.AddUObject(this, &USTUWeaponComponent::OnEquipFinished);
		
	}
	else {
		UE_LOG(LogWeaponComponent, Warning, TEXT("Equip Anim Notify Forgotten"));
			checkNoEntry();
	
	}
	
	for (auto OneWeaponData:WeaponData) {
		auto ReloadFinishedNotify = AnimUtils::FindNotifyByClass<USTUReloadAnimNotify>(OneWeaponData.ReloadAnimMontage);
		if (!ReloadFinishedNotify) {
			UE_LOG(LogWeaponComponent, Warning, TEXT("Reload Anim Notify Forgotten"));
			checkNoEntry();
		
		} 

		ReloadFinishedNotify->OnNotified.AddUObject(this, &USTUWeaponComponent::OnReloadFinished);

		


	}




}

void USTUWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComp) {
	
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character|| Character->GetMesh() != MeshComp) return;

	
	//UE_LOG(LogWeaponComponent, Warning, TEXT("AnimNotify"));
	bEquipAnimInProgress = 0;
	
	
	

}

void USTUWeaponComponent::OnReloadFinished(USkeletalMeshComponent* MeshComp) {

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || Character->GetMesh() != MeshComp) return;


	//UE_LOG(LogWeaponComponent, Warning, TEXT("AnimNotify"));
	bReloadAnimInProgress = 0;




}

bool USTUWeaponComponent::CanFire() const {

	return CurrentWeapon&&!bEquipAnimInProgress&&!bReloadAnimInProgress;
}



bool USTUWeaponComponent::CanEquip() const {

	return !bEquipAnimInProgress && !bReloadAnimInProgress;
}



void USTUWeaponComponent::OnEmptyClip() {


	ChangeClip();



}




void USTUWeaponComponent::ChangeClip() {


	if (!CanReload())return;
	CurrentWeapon->StopFire();
	CurrentWeapon->ChangeClip();
	bReloadAnimInProgress = 1;
	PlayAnimMontage(CurrentReloadAnimMontage);



}




bool USTUWeaponComponent::CanReload() const {
	return CurrentWeapon && !bEquipAnimInProgress && !bReloadAnimInProgress && CurrentWeapon->CanReload();
}

