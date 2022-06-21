// Ultimate Apex Shooter.All Rights Reserved..

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "STUNextLocationTask.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API USTUNextLocationTask : public UBTTaskNode
{
	GENERATED_BODY()
	

public:

	USTUNextLocationTask();


	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = AI)
		float Radius = 1000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		FBlackboardKeySelector AimLocationKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		bool bSelfCenter = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI,meta=(EditCondition="!bSelfCenter"))
		FBlackboardKeySelector CenterActorKey;




};
