// Ultimate Apex Shooter.All Rights Reserved..


#include "Enemy/STUAIController.h"
#include "Enemy/STUAICharacter.h"
#include "Components/STUAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"




ASTUAIController::ASTUAIController() {

	STUAIPerceptionComponent = CreateDefaultSubobject<USTUAIPerceptionComponent>("STUPerceptionComponent");
	SetPerceptionComponent(*STUAIPerceptionComponent);



}

void ASTUAIController::OnPossess(APawn* InPawn) {

	Super::OnPossess(InPawn);

	const auto STUCharacter = Cast<ASTUAICharacter>(InPawn);
	if (STUCharacter) {
		RunBehaviorTree(STUCharacter->BehaviorTreeAsset);
	}


}

AActor* ASTUAIController::GetFocusOnActor() const {





	if(!GetBlackboardComponent()) return nullptr;

	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));


}

void ASTUAIController::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);

	const auto AimActor = GetFocusOnActor();

	SetFocus(AimActor);
	

}
