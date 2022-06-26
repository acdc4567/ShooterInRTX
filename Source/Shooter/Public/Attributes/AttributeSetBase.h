// Ultimate Apex Shooter.All Rights Reserved..

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AttributeSetBase.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChangeDelegate, float, Health, float, MaxHealth);


/**
 * 
 */
UCLASS()
class SHOOTER_API UAttributeSetBase : public UAttributeSet
{
	GENERATED_BODY()
public:
	UAttributeSetBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeSet)
		FGameplayAttributeData Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeSet)
		FGameplayAttributeData MaxHealth;


	 void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;


	 FOnHealthChangeDelegate OnHealthChange;




};
