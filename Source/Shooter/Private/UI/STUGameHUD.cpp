// Ultimate Apex Shooter.All Rights Reserved..


#include "UI/STUGameHUD.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"





void ASTUGameHUD::DrawHUD() {
	Super::DrawHUD();
	DrawCrosshair();


}

void ASTUGameHUD::BeginPlay() {
	Super::BeginPlay();

	auto PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass);
	if (PlayerHUDWidget) {
		PlayerHUDWidget->AddToViewport();
	}



}

void ASTUGameHUD::DrawCrosshair() {

	int32 SizeX = Canvas->SizeX;
	int32 SizeY = Canvas->SizeY;

	const TInterval<float> Center(SizeX * .5f, SizeY * .5f);
	const float HalfLineSize = 10.f;
	const float	LineThickness = 2.f;
	const FLinearColor LineColor = FLinearColor::Green;
	DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, LineColor, LineThickness);
	DrawLine(Center.Min , Center.Max- HalfLineSize, Center.Min , Center.Max+ HalfLineSize, LineColor, LineThickness);









}
