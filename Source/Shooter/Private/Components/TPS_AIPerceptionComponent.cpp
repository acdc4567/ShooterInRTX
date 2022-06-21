// Ultimate Apex Shooter.All Rights Reserved..


#include "Components/TPS_AIPerceptionComponent.h"
#include "AIController.h"
#include "Perception/AISense_Sight.h"

#include "BehaviorTree/BlackboardComponent.h"





AActor* UTPS_AIPerceptionComponent::GetClosestEnemy() const {
    TArray<AActor*> PerceivedActors;
    GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PerceivedActors);
    if (PerceivedActors.Num() == 0) {
        return nullptr;
    }

    const auto Controller = Cast<AAIController>(GetOwner());
    if (!Controller)return nullptr;

    const auto Pawn = Controller->GetPawn();
    if (!Pawn)return nullptr;

    float BestDistance = MAX_FLT;
    AActor* BestPawn = nullptr;

/*
    for (const auto PerceivedActor : PerceivedActors) {
        const auto Component = PerceivedActor->GetComponentByClass(USTUHealthComponent::StaticClass());
        const auto HealthComponent = Cast<USTUHealthComponent>(Component);
        if (HealthComponent && !HealthComponent->IsDead()) {

            const auto CurrentDistance = (PerceivedActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
            if (CurrentDistance < BestDistance) {
                BestDistance = CurrentDistance;
                BestPawn = PerceivedActor;
            }

        }



    }
    */

    return BestPawn;


}
