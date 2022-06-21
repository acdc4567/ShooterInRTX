// Ultimate Apex Shooter.All Rights Reserved..

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "STUAIController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API ASTUAIController : public AAIController
{
	GENERATED_BODY()


public:
	ASTUAIController();


	virtual void Tick(float DeltaTime) override;

	


protected:
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		class USTUAIPerceptionComponent* STUAIPerceptionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		FName FocusOnKeyName = "EnemyActor";


private:

	AActor* GetFocusOnActor() const;


};
