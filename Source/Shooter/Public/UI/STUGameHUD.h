// Ultimate Apex Shooter.All Rights Reserved..

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "STUGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API ASTUGameHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	virtual void DrawHUD() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Movement)
		TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

	virtual void BeginPlay() override;




private:

	void DrawCrosshair();




};
