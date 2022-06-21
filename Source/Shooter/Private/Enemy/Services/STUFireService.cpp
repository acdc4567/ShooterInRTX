// Ultimate Apex Shooter.All Rights Reserved..


#include "Enemy/Services/STUFireService.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/STUWeaponComponent.h"





USTUFireService::USTUFireService() {
	NodeName = "FireService";

}

void USTUFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {

	const auto Controller = OwnerComp.GetAIOwner();
	const auto BlackBoard = OwnerComp.GetBlackboardComponent();

	const auto HasAim = BlackBoard && BlackBoard->GetValueAsObject(EnemyActorKey.SelectedKeyName);
	if (Controller) {

		const auto Component = Controller->GetPawn()->GetComponentByClass(USTUWeaponComponent::StaticClass());
		const auto WeaponComponent = Cast<USTUWeaponComponent>(Component);
		if (WeaponComponent) {
			if (HasAim) {
				WeaponComponent->StartFire();
				//UE_LOG(LogTemp, Warning, TEXT("Weapon Component Start Fire"));

			}
			else {
				WeaponComponent->StopFire();
				//UE_LOG(LogTemp, Warning, TEXT("Weapon Component Stop Fire"));

			}
			  
		}






	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);




}
