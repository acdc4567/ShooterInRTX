// Ultimate Apex Shooter.All Rights Reserved..

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "STUCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API USTUCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
public:

	virtual float GetMaxSpeed() const override;


};
