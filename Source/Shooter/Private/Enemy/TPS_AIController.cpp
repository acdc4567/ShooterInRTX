// Ultimate Apex Shooter.All Rights Reserved..


#include "Enemy/TPS_AIController.h"
#include "Enemy/TPS_AI_Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/TPS_AIPerceptionComponent.h"







ATPS_AIController::ATPS_AIController() {

	
	TPS_AIPerceptionComponent = CreateDefaultSubobject<UTPS_AIPerceptionComponent>("TPSPerceptionComponent");
	SetPerceptionComponent(*TPS_AIPerceptionComponent);



}

void ATPS_AIController::Tick(float DeltaTime) {






}

void ATPS_AIController::OnPossess(APawn* InPawn) {

	Super::OnPossess(InPawn);

	const auto TPSCharacter = Cast<ATPS_AI_Character>(InPawn);
	if (TPSCharacter) {
		RunBehaviorTree(TPSCharacter->BehaviorTreeAsset);
	}


}

AActor* ATPS_AIController::GetFocusOnActor() const {




	return nullptr;
}
