// Ultimate Apex Shooter.All Rights Reserved..


#include "Enemy/Services/STUFindEnemyService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Components/STUAIPerceptionComponent.h"




USTUFindEnemyService::USTUFindEnemyService() {

	NodeName = "Find Enemy";


}

void USTUFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	const auto BlackBoard = OwnerComp.GetBlackboardComponent();
	if (BlackBoard) {

		const auto Controller = OwnerComp.GetAIOwner();
		const auto Component = Controller->GetComponentByClass(USTUAIPerceptionComponent::StaticClass());
		const auto PerceptionComponent = Cast<USTUAIPerceptionComponent>(Component);
		if (PerceptionComponent) {
			BlackBoard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosestEnemy());
		}

	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);




}
