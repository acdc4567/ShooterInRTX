// Ultimate Apex Shooter.All Rights Reserved..

#pragma once

#include "CoreMinimal.h"
#include "Character/STUBaseCharacter.h"
#include "STUAICharacter.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API ASTUAICharacter : public ASTUBaseCharacter
{
	GENERATED_BODY()
	
public:

	ASTUAICharacter(const	 FObjectInitializer& ObjInit);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = AI)
		class UBehaviorTree* BehaviorTreeAsset;


protected:
	virtual void OnDeath() override;









};
