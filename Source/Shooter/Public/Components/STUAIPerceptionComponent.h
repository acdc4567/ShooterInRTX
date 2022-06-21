// Ultimate Apex Shooter.All Rights Reserved..

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "STUAIPerceptionComponent.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API USTUAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()
	
public:

	AActor* GetClosestEnemy() const;









};
