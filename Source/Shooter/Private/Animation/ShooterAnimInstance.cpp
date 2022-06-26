// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/ShooterAnimInstance.h"
#include "Character/ShooterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"




void UShooterAnimInstance::UpdateAnimationProperties(float DeltaTime) {


	if (ShooterCharacter == nullptr) {
		ShooterCharacter = Cast<AShooterCharacter>(TryGetPawnOwner());

	}
	if (ShooterCharacter) {

		FVector Velocity = ShooterCharacter->GetVelocity();
		Velocity.Z = 0;
		Speed = Velocity.Size();

		bIsInAir = ShooterCharacter->GetCharacterMovement()->IsFalling();


		if (ShooterCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f) {
			bIsAccelerating = 1;

		}
		else {
			bIsAccelerating = 0;
		}

		bIsCarryingTwinBlast = ShooterCharacter->GetIsCarryingTwinBlast();

		FRotator AimRotation = ShooterCharacter->GetBaseAimRotation();
		
		FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(ShooterCharacter->GetVelocity());

		MovementOffsetYaw = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation).Yaw;

		if(Speed>0.f)
		LastMovementOffsetYaw = MovementOffsetYaw;

		bAiming = ShooterCharacter->GetAiming();

		bReloading = ShooterCharacter->GetCombatState() == ECombatState::ECS_Reloading;
		
		bIsUsingAbility = ShooterCharacter->GetIsUsingAbility();


		if (bReloading) {
			OffsetState = EOffsetState::EOS_Reloading;

		}
		else if (bIsInAir) {
			OffsetState = EOffsetState::EOS_InAir;

		}
		else if (ShooterCharacter->GetAiming()) {
			OffsetState = EOffsetState::EOS_Aiming;

		}
		else  {
			OffsetState = EOffsetState::EOS_Hip;

		}

	}

	


	TurnInPlace();
	Lean(DeltaTime);


}

void UShooterAnimInstance::NativeInitializeAnimation() {

	ShooterCharacter =Cast<AShooterCharacter>(TryGetPawnOwner());




}

void UShooterAnimInstance::TurnInPlace() {


	if (ShooterCharacter == nullptr)return;
	if (Speed > 0) {

	}
	else {
		TIPCharacterYawLastFrame = TIPCharacterYaw;
		TIPCharacterYaw = ShooterCharacter->GetActorRotation().Yaw;
		const float TIPYawDelta = TIPCharacterYaw - TIPCharacterYawLastFrame;
		RootYawOffset = UKismetMathLibrary::NormalizeAxis(RootYawOffset - YawDelta);

		


	}


}

void UShooterAnimInstance::Lean(float DeltaTime) {

	if (ShooterCharacter == nullptr)return;
	CharacterRotationLastFrame = CharacterRotation;
	CharacterRotation = ShooterCharacter->GetActorRotation();
	const FRotator Delta = UKismetMathLibrary::NormalizedDeltaRotator(CharacterRotation, CharacterRotationLastFrame);

	const float Target = Delta.Yaw / DeltaTime;

	const float Interp{ FMath::FInterpTo(YawDelta,Target,DeltaTime,6.f) };

	YawDelta = FMath::Clamp(Interp, -90.f, 90.f);

	//if (GEngine)GEngine->AddOnScreenDebugMessage(0, -1, FColor::Cyan, FString::Printf(TEXT("YawDelta:%f"), YawDelta));

}
