// Ultimate Apex Shooter.All Rights Reserved..

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TakeDamage.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTakeDamage : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SHOOTER_API ITakeDamage
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void TakeDamage(float Damage, float CriticalHitModifier, FHitResult HitResult);





};
