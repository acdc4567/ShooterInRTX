// Ultimate Apex Shooter.All Rights Reserved..


#include "GameModes/STUGameModeBase.h"
#include "Character/STUBaseCharacter.h"
#include "PlayerControllers/STUPlayerController.h"
#include "UI/STUGameHUD.h"





ASTUGameModeBase::ASTUGameModeBase() {

	DefaultPawnClass = ASTUBaseCharacter::StaticClass();
	PlayerControllerClass = ASTUPlayerController::StaticClass();

	HUDClass = ASTUGameHUD::StaticClass();



}