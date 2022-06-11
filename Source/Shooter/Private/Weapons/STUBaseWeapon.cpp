// Ultimate Apex Shooter.All Rights Reserved..


#include "Weapons/STUBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Character/STUBaseCharacter.h"




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
	const auto Controller = GetPlayerController();
	if (!Controller)return 0;

	

	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
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







