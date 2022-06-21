// Ultimate Apex Shooter.All Rights Reserved..

#pragma once

#include "CoreMinimal.h"
#include "Weapons/STUBaseWeapon.h"
#include "STURifleWeapon.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API ASTURifleWeapon : public ASTUBaseWeapon
{
	GENERATED_BODY()
	
public:

	virtual void StartFire() override;
	virtual void StopFire() override;


protected:

	virtual void MakeShot() override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
		float TimeBetweenShots = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
		float BulletSpread = 1.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
		float DamageAmount = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Components)
		UParticleSystem* ImpactParticles;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Components)
		UParticleSystem* MuzzleParticles;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Components)
		UParticleSystem* BeamParticles;

	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

	void MakeDamage(const FHitResult& HitResult);

private:
	FTimerHandle ShotTimerHandle;




public:







};
