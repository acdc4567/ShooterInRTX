// Ultimate Apex Shooter.All Rights Reserved..

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TPS_AIController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API ATPS_AIController : public AAIController
{
	GENERATED_BODY()
public:

	ATPS_AIController();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		class UTPS_AIPerceptionComponent* TPS_AIPerceptionComponent;






private:

	AActor* GetFocusOnActor() const;







};
