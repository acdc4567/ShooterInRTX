// Ultimate Apex Shooter.All Rights Reserved..


#include "Character/ShooterCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Animation/AnimMontage.h"
#include "DrawDebugHelpers.h"
#include "Particles/ParticleSystemComponent.h"
#include "Weapons/Item.h"
#include "Components/WidgetComponent.h"








// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.f;
	CameraBoom->bUsePawnControlRotation = 1;


	FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->SetupAttachment(CameraBoom,USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = 0;

	bUseControllerRotationPitch = 0;
	bUseControllerRotationYaw = 1;
	bUseControllerRotationRoll = 0;

	GetCharacterMovement()->bOrientRotationToMovement = 0;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);
	GetCharacterMovement()->AirControl = .2f;






}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (FollowCamera) {
		CameraDefaultFOV = GetFollowCamera()->FieldOfView;
		CameraCurrentFOV = CameraDefaultFOV;
	}



}

void AShooterCharacter::MoveForward(float Value) {


	if (Controller != nullptr && Value != 0.f) {
		const FRotator Rotation{ Controller->GetControlRotation() };
		const FRotator YawRotation{ 0,Rotation.Yaw,0 };
		const FVector Direction{ FRotationMatrix{YawRotation}.GetUnitAxis(EAxis::X) };
	
		AddMovementInput(Direction, Value);
	
	}



}

void AShooterCharacter::MoveRight(float Value) {

	if (Controller != nullptr && Value != 0.f) {
		const FRotator Rotation{ Controller->GetControlRotation() };
		const FRotator YawRotation{ 0,Rotation.Yaw,0 };
		const FVector Direction{ FRotationMatrix{YawRotation}.GetUnitAxis(EAxis::Y) };

		AddMovementInput(Direction, Value);

	}



}

void AShooterCharacter::TurnAtRate(float Rate) {
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());





}

void AShooterCharacter::LookUpAtRate(float Rate) {

	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());




}

void AShooterCharacter::MouseTurn(float Value) {

	float TurnRatex;
	if (bAiming) {
		TurnRatex = AimTurnRate;
	}
	else {
		TurnRatex = HipTurnRate;
	}
	AddControllerYawInput(Value*TurnRatex);
}

void AShooterCharacter::MouseLookUp(float Value) {
	float TurnRatex;
	if (bAiming) {
		TurnRatex = AimLookUpRate;
	}
	else {
		TurnRatex = HipLookUpRate;
	}
	AddControllerPitchInput(Value * TurnRatex);



}

void AShooterCharacter::FireWeapon() {

	if (FireSound&&TwinFireSound) {
		if (bIsCarryingTwinBlast) {
			UGameplayStatics::PlaySound2D(this, TwinFireSound);
			
		}
		else {
			UGameplayStatics::PlaySound2D(this, FireSound);
		}

	}

	const USkeletalMeshSocket* BarrelSocket = GetMesh()->GetSocketByName("BarrelSocket");
	const USkeletalMeshSocket* BarrelSocketR = GetMesh()->GetSocketByName("BarrelSocketR");
	
	if (BarrelSocket) {
		const FTransform SocketTransform = BarrelSocket->GetSocketTransform(GetMesh());
		const FTransform SocketTransformR = BarrelSocketR->GetSocketTransform(GetMesh());
			
		if (bIsCarryingTwinBlast&& BarrelSocketR) {
			if (MuzzleFlash) {
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleFlash, SocketTransformR);

			}
		}
		
		if (MuzzleFlash) {
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleFlash, SocketTransform);
			
		}

		FVector BeamEnd;
		bool bBeamEnd = GetBeamEndLocation(SocketTransform.GetLocation(), BeamEnd);
		if (bBeamEnd) {
			if (ImpactParticles) {
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticles, BeamEnd);

			}
			if (bIsCarryingTwinBlast) {
				if (BeamParticles) {
					UParticleSystemComponent* Beam = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BeamParticles, SocketTransform);
					UParticleSystemComponent* BeamR = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BeamParticles, SocketTransformR);

					if (Beam && BeamR) {
						Beam->SetVectorParameter(FName("Target"), BeamEnd);
						BeamR->SetVectorParameter(FName("Target"), BeamEnd);

					}


				}
			}
			else {
				if (BeamParticles) {
					UParticleSystemComponent* Beam = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BeamParticles, SocketTransform);

					if (Beam) {
						Beam->SetVectorParameter(FName("Target"), BeamEnd);

					}


				}
			}



		}


	}

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (bIsCarryingTwinBlast) {
		if (AnimInstance && HipFireMontage) {
			AnimInstance->Montage_Play(HipFireMontage);
			AnimInstance->Montage_JumpToSection(FName("StartFire"));

		}
	}
	if (!bIsCarryingTwinBlast) {
		if (AnimInstance && BelicaHipFireMontage) {
			AnimInstance->Montage_Play(BelicaHipFireMontage);
			AnimInstance->Montage_JumpToSection(FName("StartFire"));

		}
	}
		
	









}

bool AShooterCharacter::GetBeamEndLocation(const FVector& MuzzleSocketLocation, FVector& OutBeamLocation) {

	FHitResult CrosshairHitResult;
	bool bCrosshairHit = TraceUnderCrosshairs(CrosshairHitResult, OutBeamLocation);
	if (bCrosshairHit) {
		OutBeamLocation = CrosshairHitResult.Location;


	}
	else {


	}

	//PerformSecondTrace

	FHitResult WeaponTraceHit;
	const FVector WeaponTraceStart = MuzzleSocketLocation;
	const FVector WeaponTraceEnd = OutBeamLocation;

	GetWorld()->LineTraceSingleByChannel(WeaponTraceHit, WeaponTraceStart, WeaponTraceEnd, ECollisionChannel::ECC_Visibility);;
	if (WeaponTraceHit.bBlockingHit) {
		OutBeamLocation = WeaponTraceHit.Location;
		return 1;

	}

	return 0;

	

}

void AShooterCharacter::AimingButtonPressed() {

	bAiming = 1;
	
}

void AShooterCharacter::AimingButtonReleased() {

	bAiming = 0;
	
}

void AShooterCharacter::CameraInterpZoom(float DeltaTime) {

	if (bAiming) {

		CameraCurrentFOV = FMath::FInterpTo(CameraCurrentFOV, CameraZoomedFOV, DeltaTime, ZoomInterpSpeed);
	}
	else {
		CameraCurrentFOV = FMath::FInterpTo(CameraCurrentFOV, CameraDefaultFOV, DeltaTime, ZoomInterpSpeed);

	}
	GetFollowCamera()->SetFieldOfView(CameraCurrentFOV);



}

void AShooterCharacter::CalculateCrosshairSpread(float DeltaTime) {

	FVector2D	WalkSpeedRange{ 0.f,600.f };
	FVector2D	VelocityMultiplierRange{ 0.f,1.f };
	FVector Velocity = GetVelocity();
	Velocity.Z = 0.f;

	CrosshairVelocityFactor = FMath::GetMappedRangeValueClamped(WalkSpeedRange, VelocityMultiplierRange, Velocity.Size());


	if (GetCharacterMovement()->IsFalling()) {
		CrosshairInAirFactor = FMath::FInterpTo(CrosshairInAirFactor, 2.25f, DeltaTime, 2.25f);
	
	}
	else {
		CrosshairInAirFactor = FMath::FInterpTo(CrosshairInAirFactor, 0.f, DeltaTime, 32.25f);

	}
	if (bAiming) {
		CrosshairAimFactor=FMath::FInterpTo(CrosshairAimFactor,.6f, DeltaTime, 32.25f);
	}
	else {
		CrosshairAimFactor = FMath::FInterpTo(CrosshairAimFactor, 0.f, DeltaTime, 32.25f);

	}


	CrosshairSpreadMultiplier = .5f + CrosshairVelocityFactor+CrosshairInAirFactor-CrosshairAimFactor;
}

void AShooterCharacter::FireButtonPressed() {

	bFireButtonPressed = 1;
	StartFireTimer();
}

void AShooterCharacter::FireButtonReleased() {

	bFireButtonPressed = 0;



}

void AShooterCharacter::StartFireTimer() {

	if (bShouldFire) {
		FireWeapon();
		bShouldFire = 0;
		GetWorldTimerManager().SetTimer(AutoFireTimer, this, &AShooterCharacter::AutoFireReset, AutomaticFireRate);
	
	
	}




}

void AShooterCharacter::AutoFireReset() {

	bShouldFire = 1;

	if (bFireButtonPressed) {
		StartFireTimer();
	}


}

bool AShooterCharacter::TraceUnderCrosshairs(FHitResult& OutHitResult, FVector& OutHitLocation) {

	//GetViewPortSize

	FVector2D ViewportSize;
	if (GEngine && GEngine->GameViewport) {

		GEngine->GameViewport->GetViewportSize(ViewportSize);

	}

	FVector CrosshairWorldPosition;
	FVector CrosshairWorldDirection;
	FVector2D CrosshairLocation(ViewportSize.X / 2.f, ViewportSize.Y / 2.f);

	bool bScreenToWorld = UGameplayStatics::DeprojectScreenToWorld(UGameplayStatics::GetPlayerController(this, 0), CrosshairLocation, CrosshairWorldPosition, CrosshairWorldDirection);
	if (bScreenToWorld) {
		const FVector Start = CrosshairWorldPosition;
		const FVector End = Start + CrosshairWorldDirection * 80'000.f;
		OutHitLocation = End;
		GetWorld()->LineTraceSingleByChannel(OutHitResult, Start, End, ECollisionChannel::ECC_Visibility);

		if (OutHitResult.bBlockingHit) {
			OutHitLocation = OutHitResult.Location;
			return 1;
		}
	}



	return false;
}

float AShooterCharacter::GetCrosshairSpreadMultipler() const {
	return CrosshairSpreadMultiplier;
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CameraInterpZoom(DeltaTime);
	CalculateCrosshairSpread(DeltaTime);

	FHitResult ItemTraceResult;
	FVector HitLocation;
	TraceUnderCrosshairs(ItemTraceResult, HitLocation);

	if (ItemTraceResult.bBlockingHit) {
		AItem* HitItem = Cast<AItem>(ItemTraceResult.GetActor());
		if (HitItem&&HitItem->GetPickupWidget()) {
			HitItem->GetPickupWidget()->SetVisibility(1);
		}


	}


}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);


	PlayerInputComponent->BindAxis("MoveForward", this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AShooterCharacter::MoveRight);

	PlayerInputComponent->BindAxis("TurnRate", this, &AShooterCharacter::MouseTurn);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AShooterCharacter::MouseLookUp);

	PlayerInputComponent->BindAxis("Turn", this, &AShooterCharacter::MouseTurn);
	PlayerInputComponent->BindAxis("LookUp", this, &AShooterCharacter::MouseLookUp);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AShooterCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AShooterCharacter::StopJumping);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AShooterCharacter::FireButtonPressed);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AShooterCharacter::FireButtonReleased);

	PlayerInputComponent->BindAction("AimingButton", IE_Pressed, this, &AShooterCharacter::AimingButtonPressed);
	PlayerInputComponent->BindAction("AimingButton", IE_Released, this, &AShooterCharacter::AimingButtonReleased);


}

