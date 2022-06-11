// Ultimate Apex Shooter.All Rights Reserved..


#include "Weapons/STURifleWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Character/STUBaseCharacter.h"


void ASTURifleWeapon::StartFire() {

	MakeShot();
	GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ASTURifleWeapon::MakeShot, TimeBetweenShots, 1);

}

void ASTURifleWeapon::StopFire() {

	GetWorldTimerManager().ClearTimer(ShotTimerHandle);


}

void ASTURifleWeapon::MakeShot() {
	if (!GetWorld())return;

	FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd)) return;

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	if (HitResult.bBlockingHit) {
		MakeDamage(HitResult);
		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Cyan, 0, 3.f, 0, 3.f);

		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.f, 24, FColor::Red, 0, 5.f);
		//UE_LOG(LogBaseWeapon, Warning, TEXT("Bone : %s"), *HitResult.BoneName.ToString());
	}
	else {
		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), TraceEnd, FColor::Green, 0, 3.f, 0, 3.f);

	}

}

bool ASTURifleWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const {


	FVector ViewLocation;
	FRotator ViewRotation;
	if (!GetPlayerViewPoint(ViewLocation, ViewRotation))return 0;

	const auto STUPlayer = Cast<ASTUBaseCharacter>(GetPlayerCharacter());
	if (!STUPlayer)return 0;

	const auto SpringArmDistance = STUPlayer->GetSpringArm()->TargetArmLength + 100.f;
	
	const auto HalfRad = FMath::DegreesToRadians(BulletSpread);
	FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
	TraceStart = ViewLocation + ShootDirection * SpringArmDistance;
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
	return 1;

	
}

void ASTURifleWeapon::MakeDamage(const FHitResult& HitResult) {

	const auto DamagedActor = HitResult.GetActor();
	if (!DamagedActor)return;

	DamagedActor->TakeDamage(DamageAmount, FDamageEvent(), GetPlayerController(), this);



}