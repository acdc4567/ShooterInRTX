// Ultimate Apex Shooter.All Rights Reserved..


#include "Weapons/STULauncherWeapon.h"
#include "Weapons/STUProjectile.h"
#include "Kismet/GameplayStatics.h"



void ASTULauncherWeapon::StartFire() {
	MakeShot();

}

void ASTULauncherWeapon::MakeShot() {
	
	if (!GetWorld())return;

	FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd)) return;

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
	const FVector Direction = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();



	const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
	//auto Projectile = UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), ProjectileClass, SpawnTransform);
	ASTUProjectile* Projectile = GetWorld()->SpawnActorDeferred<ASTUProjectile>(ProjectileClass, SpawnTransform);
	if (Projectile) {

		Projectile->SetShotDirection(Direction);
		Projectile->SetOwner(GetOwner());
		Projectile->FinishSpawning(SpawnTransform);
	}


	UGameplayStatics::FinishSpawningActor(Projectile, SpawnTransform);




}
