// Ultimate Apex Shooter.All Rights Reserved..


#include "Weapons/STUBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Character/STUBaseCharacter.h"
#include "Enemy/STUAICharacter.h"
#include "Enemy/STUAIController.h"
#include "Kismet/KismetMathLibrary.h"



DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);

// Sets default values
ASTUBaseWeapon::ASTUBaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = 0;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);






}

void ASTUBaseWeapon::StartFire() {

	
}

void ASTUBaseWeapon::StopFire() {
	
}




// Called when the game starts or when spawned
void ASTUBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	check(WeaponMesh);
	checkf(DefaultAmmo.Bullets > 0, TEXT("bullet count cannot be 0"));
	checkf(DefaultAmmo.Clips > 0, TEXT("Clips count cannot be 0"));



	CurrentAmmo = DefaultAmmo;



}

void ASTUBaseWeapon::MakeShot() {
	
}

ACharacter* ASTUBaseWeapon::GetPlayerCharacter() const {
	return Cast<ACharacter>(GetOwner());
}

APlayerController* ASTUBaseWeapon::GetPlayerController() const {
	const auto Player = GetPlayerCharacter();
	if (!Player)return nullptr;

	
	return Player->GetController<APlayerController>();
}

bool ASTUBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const {
	
	const auto STUCharacter = Cast<ACharacter>(GetOwner());
	if (!STUCharacter)return 0;

	if (STUCharacter->IsPlayerControlled()) {

		const auto Controller = GetPlayerController();
		if (!Controller)return 0;

		Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);


	}
	else {

		const auto STUAICharacter = Cast<ASTUAICharacter>(GetOwner());
		if (STUAICharacter) {
			//UE_LOG(LogBaseWeapon, Warning, TEXT("AICharacterCast"));
			const auto Controller = Cast<ASTUAIController>(STUAICharacter->GetController());
			if (Controller) {
				//UE_LOG(LogBaseWeapon, Warning, TEXT("AIControllerrCast"));
				ViewLocation = GetMuzzleWorldLocation();
				ViewRotation= UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Controller->GetFocalPoint());



			}
		}
		
		else {
			ViewLocation = GetMuzzleWorldLocation();
			ViewRotation = STUCharacter->GetActorRotation();
		}
		
		
		
	}


	
	
	return 1;
}

FVector ASTUBaseWeapon::GetMuzzleWorldLocation() const {
	return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

bool ASTUBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const {
	FVector ViewLocation;
	FRotator ViewRotation;
	if(! GetPlayerViewPoint(ViewLocation, ViewRotation))return 0;

	const auto STUPlayer = Cast<ASTUBaseCharacter>(GetPlayerCharacter());
	if (!STUPlayer)return 0;

	const auto SpringArmDistance = STUPlayer->GetSpringArm()->TargetArmLength + 100.f;
	FVector ShootDirection = ViewRotation.Vector();
	TraceStart = ViewLocation + ShootDirection * SpringArmDistance;
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
	return 1;


}

void ASTUBaseWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd) {
	if (!GetWorld())return;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());
	

	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);



}

void ASTUBaseWeapon::DecreaseAmmo() {
	if (CurrentAmmo.Bullets == 0) {
		UE_LOG(LogBaseWeapon, Warning, TEXT("No More Bullets..Clip Is Empty"));
		return;
	}
	CurrentAmmo.Bullets--;
	//LogAmmo();

	if (IsClipEmpty() && !IsAmmoEmpty()) {
		StopFire();
		OnClipEmpty.Broadcast();

	}


}

bool ASTUBaseWeapon::IsAmmoEmpty() const {


	return !CurrentAmmo.bInfinite&&CurrentAmmo.Clips==0&&IsClipEmpty();
}

bool ASTUBaseWeapon::IsClipEmpty() const {

	
	return CurrentAmmo.Bullets==0;

}

void ASTUBaseWeapon::ChangeClip() {

	if (!CurrentAmmo.bInfinite) {
		if (CurrentAmmo.Clips==0) {
			UE_LOG(LogBaseWeapon, Warning, TEXT("No More Clips"));
			return;
		}
		CurrentAmmo.Clips--;
	}
	CurrentAmmo.Bullets = DefaultAmmo.Bullets;

	//UE_LOG(LogBaseWeapon, Warning, TEXT("----------ChangeClip----------"));

}

bool ASTUBaseWeapon::CanReload() const {




	return CurrentAmmo.Bullets < DefaultAmmo.Bullets&& CurrentAmmo.Clips>0;
}

void ASTUBaseWeapon::LogAmmo() {
	FString AmmoInfo = "Ammo : " + FString::FromInt(CurrentAmmo.Bullets) + " / ";
	AmmoInfo += CurrentAmmo.bInfinite ? "Infinite" : FString::FromInt(CurrentAmmo.Clips);
	UE_LOG(LogBaseWeapon, Warning, TEXT("%s"), *AmmoInfo);

}







