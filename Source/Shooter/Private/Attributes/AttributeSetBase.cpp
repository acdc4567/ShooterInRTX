// Ultimate Apex Shooter.All Rights Reserved..


#include "Attributes/AttributeSetBase.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffect.h"



UAttributeSetBase::UAttributeSetBase()
	:Health(200.f)
	,MaxHealth(200.f)
{




}

void UAttributeSetBase::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) {
	//UE_LOG(LogTemp, Warning, TEXT("PostFGameplay"));

	if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<FProperty>(UAttributeSetBase::StaticClass(), GET_MEMBER_NAME_CHECKED(UAttributeSetBase, Health))) {
		//UE_LOG(LogTemp, Warning, TEXT("Damage Taken,Health : %f"), Health.GetCurrentValue());
		Health.SetCurrentValue(FMath::Clamp(Health.GetCurrentValue(), 0.f, MaxHealth.GetCurrentValue()));
		Health.SetBaseValue(FMath::Clamp(Health.GetBaseValue(), 0.f, MaxHealth.GetCurrentValue()));
		OnHealthChange.Broadcast(Health.GetCurrentValue(), MaxHealth.GetCurrentValue());
	}
}	

