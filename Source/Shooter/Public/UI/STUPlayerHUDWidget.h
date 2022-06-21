// Ultimate Apex Shooter.All Rights Reserved..

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUPlayerHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API USTUPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	


public:

	UFUNCTION(BlueprintCallable, Category = UI)
		float GetHealthPercent() const;












};
