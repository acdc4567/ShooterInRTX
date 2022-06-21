// Ultimate Apex Shooter.All Rights Reserved..

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "STUEnemyEnvQueryContext.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API USTUEnemyEnvQueryContext : public UEnvQueryContext
{
	GENERATED_BODY()
public:


	virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
		FName EnemyActorKeyName = "EnemyActor";




};
