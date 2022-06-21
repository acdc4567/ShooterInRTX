// Ultimate Apex Shooter.All Rights Reserved..


#include "UI/STUPlayerHUDWidget.h"
#include "Components/STUHealthComponent.h"



float USTUPlayerHUDWidget::GetHealthPercent() const {
	const auto Player = GetOwningPlayerPawn();
	if (!Player) {
		return 0.f;
	}

	const auto Component = Player->GetComponentByClass(USTUHealthComponent::StaticClass());
	const auto HealthComponent = Cast<USTUHealthComponent>(Component);
	if (!HealthComponent)return 0.f;
	return HealthComponent->GetHealthPercent();

}
