// Ultimate Apex Shooter.All Rights Reserved..

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "TPS_AIPerceptionComponent.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API UTPS_AIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()


public:

	AActor* GetClosestEnemy() const;

	

};
