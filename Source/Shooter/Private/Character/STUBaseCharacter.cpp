// Ultimate Apex Shooter.All Rights Reserved..


#include "Character/STUBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/STUCharacterMovementComponent.h"
#include "Components/STUHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Controller.h"
#include "Components/STUWeaponComponent.h"
#include "Components/CapsuleComponent.h"





DEFINE_LOG_CATEGORY_STATIC(BaseCharacterLog, All, All);



// Sets default values
ASTUBaseCharacter::ASTUBaseCharacter(const	 FObjectInitializer& ObjInit):Super(ObjInit.SetDefaultSubobjectClass<USTUCharacterMovementComponent>(ACharacter::CharacterMovementComponentName)){
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent=CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SocketOffset=FVector(0.f,80.f,80.f);
	SpringArmComponent->SetupAttachment(GetRootComponent());

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	HealthComponent = CreateDefaultSubobject<USTUHealthComponent>("HealthComponent");

	HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
	HealthTextComponent->SetupAttachment(GetRootComponent());
	HealthTextComponent->SetOwnerNoSee(1);

	WeaponComponent = CreateDefaultSubobject<USTUWeaponComponent>("WeaponComponent");





}

// Called when the game starts or when spawned
void ASTUBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	check(HealthComponent);
	check(HealthTextComponent);
	check(GetCharacterMovement());


	OnHealthChanged(HealthComponent->GetHealth());
	HealthComponent->OnDeath.AddUObject(this, &ASTUBaseCharacter::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &ASTUBaseCharacter::OnHealthChanged);

	LandedDelegate.AddDynamic(this, &ASTUBaseCharacter::OnGroundLanded);

	





}

void ASTUBaseCharacter::TakeDamagePressed() {


	//TakeDamage(10.f, FDamageEvent{}, Controller, this);


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
	check(WeaponComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASTUBaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASTUBaseCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &ASTUBaseCharacter::TurnAround);
	PlayerInputComponent->BindAxis("LookUp", this, &ASTUBaseCharacter::LookUp);

	PlayerInputComponent->BindAction("Jump", IE_Pressed,this, &ASTUBaseCharacter::Jump);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASTUBaseCharacter::OnStartRunning);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ASTUBaseCharacter::OnStopRunning);

	PlayerInputComponent->BindAction("Select", IE_Pressed, this, &ASTUBaseCharacter::TakeDamagePressed);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &USTUWeaponComponent::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &USTUWeaponComponent::StopFire);





}

bool ASTUBaseCharacter::IsRunning() const {


	return bWantsToRun&&bIsMovingForward&&!GetVelocity().IsZero();
}

float ASTUBaseCharacter::GetMovementDirection() const {
	if (GetVelocity().IsZero())return 0.f;
	const auto VelocityNormal = GetVelocity().GetSafeNormal();
	const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
	const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
	const auto Degrees = FMath::RadiansToDegrees(AngleBetween);
	
	return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
	
}



void ASTUBaseCharacter::MoveForward(float Amount) {
	bIsMovingForward = Amount > 0.f;
	if (Amount == 0.f)return;
	AddMovementInput(GetActorForwardVector(),Amount);

}

void ASTUBaseCharacter::MoveRight(float Amount) {
	if (Amount == 0.f)return;
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

void ASTUBaseCharacter::OnDeath() {

	PlayAnimMontage(DeathAnimMontage);
	GetCharacterMovement()->DisableMovement();
	SetLifeSpan(5.f);

	if (Controller) {
		Controller->ChangeState(NAME_Spectating);
	}

	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);



}

void ASTUBaseCharacter::OnHealthChanged(float Health) {
	
	HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));



}

void ASTUBaseCharacter::OnGroundLanded(const FHitResult& Hit) {

	const auto FallVelocityZ = GetCharacterMovement()->Velocity.Z;
	if (-FallVelocityZ < LandedDamageVelocity.X)return;
	const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, -FallVelocityZ);
	
	
	TakeDamage(FinalDamage, FDamageEvent{}, nullptr, nullptr);




}







