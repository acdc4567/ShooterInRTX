// Ultimate Apex Shooter.All Rights Reserved..


#include "Enemy/STUAICharacter.h"
#include "Enemy/STUAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/STUAIWeaponComponent.h"
#include "BrainComponent.h"




ASTUAICharacter::ASTUAICharacter(const FObjectInitializer& ObjInit) :Super(ObjInit.SetDefaultSubobjectClass<USTUAIWeaponComponent>("WeaponComponent")) {

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ASTUAIController::StaticClass();

	bUseControllerRotationYaw = 0;
	if (GetCharacterMovement()) {
		GetCharacterMovement()->bUseControllerDesiredRotation = 1;
		GetCharacterMovement()->RotationRate = FRotator(0.f, 200.f, 0.f);
	}

	



}

void ASTUAICharacter::OnDeath() {









	Super::OnDeath();

	const auto STUCOntroller = Cast<AAIController>(Controller);
	if (STUCOntroller && STUCOntroller->BrainComponent) {

		STUCOntroller->BrainComponent->Cleanup();
	}





}
