// Ultimate Apex Shooter.All Rights Reserved..


#include "Character/STUBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"






// Sets default values
ASTUBaseCharacter::ASTUBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent=CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);







}

// Called when the game starts or when spawned
void ASTUBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASTUBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASTUBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);


	PlayerInputComponent->BindAxis("MoveForward", this, &ASTUBaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASTUBaseCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &ASTUBaseCharacter::TurnAround);
	PlayerInputComponent->BindAxis("LookUp", this, &ASTUBaseCharacter::LookUp);

	PlayerInputComponent->BindAction("Jump", IE_Pressed,this, &ASTUBaseCharacter::Jump);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASTUBaseCharacter::OnStartRunning);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ASTUBaseCharacter::OnStopRunning);







}

bool ASTUBaseCharacter::IsRunning() const {


	return bWantsToRun&&bIsMovingForward&&!GetVelocity().IsZero();
}



void ASTUBaseCharacter::MoveForward(float Amount) {
	bIsMovingForward = Amount > 0.f;

	AddMovementInput(GetActorForwardVector(),Amount);

}

void ASTUBaseCharacter::MoveRight(float Amount) {

	AddMovementInput(GetActorRightVector(), Amount);


}

void ASTUBaseCharacter::LookUp(float Amount) {

	AddControllerPitchInput(Amount * .7f);

}

void ASTUBaseCharacter::TurnAround(float Amount) {

	AddControllerYawInput(Amount * .7f);


}

void ASTUBaseCharacter::OnStartRunning() {

	bWantsToRun = 1;



}

void ASTUBaseCharacter::OnStopRunning() {

	bWantsToRun = 0;

}



