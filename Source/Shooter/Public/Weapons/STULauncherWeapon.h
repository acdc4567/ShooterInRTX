// Ultimate Apex Shooter.All Rights Reserved..

#pragma once

#include "CoreMinimal.h"
#include "Weapons/STUBaseWeapon.h"
#include "STULauncherWeapon.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API ASTULauncherWeapon : public ASTUBaseWeapon
{
	GENERATED_BODY()

public:

	virtual void StartFire() override;

protected:

	virtual void MakeShot() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
		TSubclassOf<class ASTUProjectile> ProjectileClass;








};
