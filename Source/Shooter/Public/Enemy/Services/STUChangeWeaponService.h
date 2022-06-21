// Ultimate Apex Shooter.All Rights Reserved..

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "STUChangeWeaponService.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API USTUChangeWeaponService : public UBTService
{
	GENERATED_BODY()
	
public:
	USTUChangeWeaponService();


protected:

	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		float Probability = .5f;


};
