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


private:

	void DrawCrosshair();




};
