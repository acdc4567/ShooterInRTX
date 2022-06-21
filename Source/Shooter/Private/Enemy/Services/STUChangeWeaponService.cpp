// Ultimate Apex Shooter.All Rights Reserved..


#include "Enemy/Services/STUChangeWeaponService.h"
#include "Components/STUWeaponComponent.h"
#include "AIController.h"






USTUChangeWeaponService::USTUChangeWeaponService() {


	NodeName = "ChangeWeapon";



}





void USTUChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {



	const auto Controller = OwnerComp.GetAIOwner();

	if (Controller) {
		const auto Component = Controller->GetPawn()-> GetComponentByClass(USTUWeaponComponent::StaticClass());
		const auto WeaponComponent = Cast<USTUWeaponComponent>(Component);


		if (WeaponComponent&&Probability>0.f&&FMath::FRand()<=Probability) {
			WeaponComponent->NextWeapon();
		}

	}









	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

}


