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
#include "Weapons/Weapon.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Ammunition/Ammo.h"
#include "Interfaces/BulletHitInterface.h"
#include "Enemy/Enemy.h"
#include "Attributes/AttributeSetBase.h"
#include "Components/CapsuleComponent.h"
#include "Character/ShooterEnemyCharacter.h"
#include "AIController.h"
#include "GameFramework/PlayerController.h"
#include "BrainComponent.h"








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

	SwordMesh = CreateDefaultSubobject<UStaticMeshComponent>("SwordMesh");
	SwordMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SwordMesh->SetupAttachment(GetRootComponent());

	LHandSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("LHandSceneComp"));

	AbilitySystemComp = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComp");

	AttributeSetBaseComp = CreateDefaultSubobject<UAttributeSetBase>("AttributeSetBaseComp");

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>("CapsuleComp");
	CapsuleComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CapsuleComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CapsuleComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	CapsuleComp->SetupAttachment(GetMesh(),FName("RightHandSocketTwinR"));







}

void AShooterCharacter::AutoDetermineTeamID() {

	if (GetController()&&GetController()->IsPlayerController()) {
		TeamId = 0;
	}
}

void AShooterCharacter::Deadxc() {
	APlayerController* PC = Cast<APlayerController>(GetController());

	if (PC) {
		PC->DisableInput(PC);
	}
	AAIController* AIC = Cast<AAIController>(GetController());
	if (AIC) {
		AIC->GetBrainComponent()->StopLogic("Dead");
	}

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	check(AbilitySystemComp);
	check(AttributeSetBaseComp);
	check(CapsuleComp);

	AttributeSetBaseComp->OnHealthChange.AddDynamic(this, &AShooterCharacter::OnHealthxChanged);

	if (FollowCamera) {
		CameraDefaultFOV = GetFollowCamera()->FieldOfView;
		CameraCurrentFOV = CameraDefaultFOV;
	}
	EquipWeapon(SpawnDefaultWeapon());
	EquippedWeapon->DisableCustomDepth();
	EquippedWeapon->DIsableGlowMaterial();

	if (SwordMesh) {
		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
		
		SwordMesh->AttachToComponent(GetMesh(), AttachmentRules, FName(TEXT("RightHandSocketTwinR")));

	}


	CapsuleComp->OnComponentBeginOverlap.AddDynamic(this,&AShooterCharacter::OnSwordOverlap);
		
	AutoDetermineTeamID();

	InitializeAmmoMap();

	if (AbilitToAquire) {
		AquireAbility(AbilitToAquire);
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

	if (EquippedWeapon == nullptr)return;
	if (CombatState != ECombatState::ECS_UnOccupied)return;

	if (WeaponHasAmmo()) {
		//sound
		PlayFireSound();

		//sendbullet
		SendBullet();




		//playHipifiremontage
		PlayGunFireMontage();

		EquippedWeapon->DecrementAmmo();

		StartFireTimer();

	}
	
		
	
	









}

bool AShooterCharacter::GetBeamEndLocation(const FVector& MuzzleSocketLocation, FHitResult& OutHitResult) {


	FVector OutBeamLocation;

	FHitResult CrosshairHitResult;
	bool bCrosshairHit = TraceUnderCrosshairs(CrosshairHitResult, OutBeamLocation);
	if (bCrosshairHit) {
		OutBeamLocation = CrosshairHitResult.Location;


	}
	else {


	}

	//PerformSecondTrace

	
	const FVector WeaponTraceStart = MuzzleSocketLocation;
	const FVector StartToEnd = OutBeamLocation - MuzzleSocketLocation;


	const FVector WeaponTraceEnd = MuzzleSocketLocation+StartToEnd*1.25f;

	GetWorld()->LineTraceSingleByChannel(OutHitResult, WeaponTraceStart, WeaponTraceEnd, ECollisionChannel::ECC_Visibility);;
	if (!OutHitResult.bBlockingHit) {
		OutHitResult.Location = OutBeamLocation;
		return 0;

	}

	return 1;

	

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
	if (!bIsUsingAbility) {
		bFireButtonPressed = 1;
		FireWeapon();
	}
	else {
		OneKeyPressed();
		/*
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance && MeleeMontage) {
			AnimInstance->Montage_Play(MeleeMontage);
			AnimInstance->Montage_JumpToSection(FName("StartMelee"));

		}*/

		if (AbilitToAquire) {
			AbilitySystemComp->TryActivateAbilityByClass(AbilitToAquire);
		}
		




	}
	
}

void AShooterCharacter::FireButtonReleased() {
	if (!bIsUsingAbility) {
		bFireButtonPressed = 0;
	}
	



}

void AShooterCharacter::OneKeyPressed() {

	if (EquippedWeapon) {
		EquippedWeapon->GetItemMesh()->SetVisibility(!bItemVisibility);
		if (bIsUsingAbility) {
			bItemVisibility = 1;
		}
		else {
			bItemVisibility = 0;
		}
	}

}

void AShooterCharacter::StartFireTimer() {

	CombatState = ECombatState::ECS_FireTimerInProgress;

	GetWorldTimerManager().SetTimer(AutoFireTimer, this, &AShooterCharacter::AutoFireReset, AutomaticFireRate);


}

void AShooterCharacter::AutoFireReset() {
	CombatState = ECombatState::ECS_UnOccupied;
	if (WeaponHasAmmo()) {
		if (bFireButtonPressed) {
			FireWeapon();
		}
	}
	else {
		ReloadWeapon();
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

void AShooterCharacter::TraceForItems() {
	if (bShouldTraceForItems) {
		FHitResult ItemTraceResult;
		FVector HitLocation;
		TraceUnderCrosshairs(ItemTraceResult, HitLocation);

		if (ItemTraceResult.bBlockingHit) {
			TraceHitItem = Cast<AItem>(ItemTraceResult.GetActor());
			if (TraceHitItem && TraceHitItem->GetPickupWidget()) {
				TraceHitItem->GetPickupWidget()->SetVisibility(1);
				TraceHitItem->EnableCustomDepth();
			
			}

			if (TraceHitItemLastFrame) {
				if (TraceHitItem != TraceHitItemLastFrame) {

					TraceHitItemLastFrame->GetPickupWidget()->SetVisibility(0);
					TraceHitItemLastFrame->DisableCustomDepth();



				}
			
			}

			TraceHitItemLastFrame = TraceHitItem;

		}
	}
	else if (TraceHitItemLastFrame) {
		TraceHitItemLastFrame->GetPickupWidget()->SetVisibility(0);
		TraceHitItemLastFrame->DisableCustomDepth();
	}


}

 AWeapon* AShooterCharacter::SpawnDefaultWeapon() {
	
	
	if (DefaultWeaponClass) {
		return GetWorld()->SpawnActor<AWeapon>(DefaultWeaponClass);
		
		
	}
	return nullptr;


}

 void AShooterCharacter::PickupAmmo( AAmmo* Ammo) {


	 if (AmmoMap.Find(Ammo->GetAmmoType())) {
		 int32 AmmoCount = AmmoMap[Ammo->GetAmmoType()];
		 AmmoCount += Ammo->GetItemCount();
		 AmmoMap[Ammo->GetAmmoType()] = AmmoCount;
		 if (EquippedWeapon->GetAmmoType() == Ammo->GetAmmoType()) {
			 if (EquippedWeapon->GetAmmo() == 0) {
				 ReloadWeapon();
			 }
		 }
		 Ammo->Destroy();


	 }


 }

 void AShooterCharacter::OnSwordOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	 AShooterCharacter* EnemyCharacter = Cast<AShooterCharacter>(OtherActor);
	 if (EnemyCharacter&&EnemyCharacter->TeamId!=this->TeamId) {
		 //UE_LOG(LogTemp, Warning, TEXT("EnemyCharacter"));
		 
		 SendingGameplayEventToActor(OtherActor);
	 }
 
 
 
 
 
 }

 void AShooterCharacter::OnHealthxChanged(float Health, float MaxHealth) {
	 
	 BP_OnHealthChanged(Health, MaxHealth);
	 if (Health <= 0.f&&!bIsDead) {
		 bIsDead = 1;
		 UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		 if (AnimInstance && DeathAMontage) {
			 AnimInstance->Montage_Play(DeathAMontage);
			 AnimInstance->Montage_JumpToSection(FName("DeathA"));

		 }
		 Deadxc();
		 SetLifeSpan(5.f);
	 }

 }

void AShooterCharacter::EquipWeapon(AWeapon* WeaponToEquip) {

	

	 

	if (WeaponToEquip->GetIsTwinBlast()) {
		const USkeletalMeshSocket* HandSocketR = GetMesh()->GetSocketByName(FName("RightHandSocketTwinR"));
		if ( HandSocketR) {
			
			HandSocketR->AttachActor(WeaponToEquip, GetMesh());
		}
		if (WeaponToEquip->GetItemMeshx2()) {
			FAttachmentTransformRules AttachmentRules(EAttachmentRule::KeepRelative, true);

			WeaponToEquip->GetItemMeshx2()->AttachToComponent(GetMesh(), AttachmentRules, FName(TEXT("RightHandSocketTwinRs")));
		}
		bIsCarryingTwinBlast = WeaponToEquip->GetIsTwinBlast();
		
	}

	if (!WeaponToEquip->GetIsTwinBlast()) {
		const USkeletalMeshSocket* HandSocket = GetMesh()->GetSocketByName(FName("RightHandSocket"));
		if (HandSocket) {
			HandSocket->AttachActor(WeaponToEquip, GetMesh());
		}
		bIsCarryingTwinBlast = WeaponToEquip->GetIsTwinBlast();
	}
		
	EquippedWeapon = WeaponToEquip;
	EquippedWeapon->SetItemState(EItemState::EIS_Equipped);
	



}

void AShooterCharacter::DropWeapon() {
	if (EquippedWeapon) {
		FDetachmentTransformRules DetachmentTransformRules(EDetachmentRule::KeepWorld, 1);;
		EquippedWeapon->GetItemMesh()->DetachFromComponent(DetachmentTransformRules);
		if (EquippedWeapon->GetItemMeshx2()) {
			EquippedWeapon->GetItemMeshx2()->DetachFromComponent(DetachmentTransformRules);

		}
		EquippedWeapon->SetItemState(EItemState::EIS_Falling);
		EquippedWeapon->ThrowWeapon();
		EquippedWeapon->SetLifeSpan(5.f);
	
	}





}

void AShooterCharacter::SelectButtonPressed() {
	if (TraceHitItem) {
		TraceHitItem->StartItemCurve(this);

		


	}
	

}

void AShooterCharacter::SelectButtonReleased() {



}

void AShooterCharacter::SwapWeapon(AWeapon* WeaponToSwap) {
	DropWeapon();
	EquipWeapon(WeaponToSwap);
	TraceHitItem = nullptr;
	TraceHitItemLastFrame = nullptr;

}

void AShooterCharacter::InitializeAmmoMap() {

	AmmoMap.Add(EAmmoType::EAT_9mm, Starting9mmAmmo);
	AmmoMap.Add(EAmmoType::EAT_AR, StartingARAmmo);


}

bool AShooterCharacter::WeaponHasAmmo() {

	if (EquippedWeapon == nullptr)return 0;
	return EquippedWeapon->GetAmmo()>0;
}

void AShooterCharacter::PlayFireSound() {

	if (FireSound && TwinFireSound) {
		if (bIsCarryingTwinBlast) {
			UGameplayStatics::PlaySound2D(this, TwinFireSound);

		}
		else {
			UGameplayStatics::PlaySound2D(this, FireSound);
		}

	}


}

void AShooterCharacter::SendBullet() {

	if (bIsCarryingTwinBlast) {
		const USkeletalMeshSocket* BarrelSocket = GetMesh()->GetSocketByName("BarrelSocket");
		const USkeletalMeshSocket* BarrelSocketR = GetMesh()->GetSocketByName("BarrelSocketR");
		if (BarrelSocket && BarrelSocketR) {
			const FTransform SocketTransform = BarrelSocket->GetSocketTransform(GetMesh());
			const FTransform SocketTransformR = BarrelSocketR->GetSocketTransform(GetMesh());
			if (MuzzleFlash) {
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleFlash, SocketTransform);

				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleFlash, SocketTransformR);
			}
			FHitResult BeamHitResult;
			bool bBeamEnd = GetBeamEndLocation(SocketTransform.GetLocation(), BeamHitResult);
			if (bBeamEnd) {

				if (BeamHitResult.GetActor()) {
					IBulletHitInterface* BulletHitInterface=Cast<IBulletHitInterface>(BeamHitResult.GetActor());
					if (BulletHitInterface) {

						BulletHitInterface->BulletHit_Implementation(BeamHitResult);

					}
					AEnemy* HitEnemy = Cast<AEnemy>(BeamHitResult.GetActor());
					if (HitEnemy) {
						UGameplayStatics::ApplyDamage(BeamHitResult.GetActor(), EquippedWeapon->GetDamage(), GetController(), this, UDamageType::StaticClass());
					}


				}
				else {
				
					if (ImpactParticles) {
						UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticles, BeamHitResult.Location);

					}
				}

				
				if (BeamParticles) {
					UParticleSystemComponent* Beam = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BeamParticles, SocketTransform);
					UParticleSystemComponent* BeamR = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BeamParticles, SocketTransformR);

					if (Beam && BeamR) {
						Beam->SetVectorParameter(FName("Target"), BeamHitResult.Location);
						BeamR->SetVectorParameter(FName("Target"), BeamHitResult.Location);

					}


				}
			}

		}
	}
	else {
		const USkeletalMeshSocket* BarrelSocket = EquippedWeapon->GetItemMesh()->GetSocketByName("BarrelSocket");
		if (BarrelSocket) {
			const FTransform SocketTransform = BarrelSocket->GetSocketTransform(EquippedWeapon->GetItemMesh());
			if (MuzzleFlash) {
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleFlash, SocketTransform);

			}
			FHitResult BeamHitResult;
			//FVector BeamEnd;
			bool bBeamEnd = GetBeamEndLocation(SocketTransform.GetLocation(), BeamHitResult);
			if (bBeamEnd) {

				if (BeamHitResult.GetActor()) {
					IBulletHitInterface* BulletHitInterface = Cast<IBulletHitInterface>(BeamHitResult.GetActor());
					if (BulletHitInterface) {

						BulletHitInterface->BulletHit_Implementation(BeamHitResult);

					}
					AEnemy* HitEnemy = Cast<AEnemy>(BeamHitResult.GetActor());
					if (HitEnemy) {
						UGameplayStatics::ApplyDamage(BeamHitResult.GetActor(), EquippedWeapon->GetDamage(), GetController(), this, UDamageType::StaticClass());
					}

				}

				else {
					if (ImpactParticles) {
						UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticles, BeamHitResult.Location);

					}
				}


				
				if (BeamParticles) {
					UParticleSystemComponent* Beam = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BeamParticles, SocketTransform);

					if (Beam) {
						Beam->SetVectorParameter(FName("Target"), BeamHitResult.Location);

					}


				}
			}


		}
	}






}

void AShooterCharacter::PlayGunFireMontage() {

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

void AShooterCharacter::ReloadButtonPressed() {

	ReloadWeapon();

}

void AShooterCharacter::ReloadWeapon() {
	if (CombatState != ECombatState::ECS_UnOccupied) return;
	if (EquippedWeapon == nullptr)return;

	
	if (CarryingAmmo()&&!EquippedWeapon->ClipIsFull()) {
		
		

		CombatState = ECombatState::ECS_Reloading;
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance && ReloadMontage) {
			AnimInstance->Montage_Play(ReloadMontage);
			AnimInstance->Montage_JumpToSection(EquippedWeapon->GetReloadMontageSectionName());
		
		}
	}


}

bool AShooterCharacter::CarryingAmmo() {

	if (EquippedWeapon == nullptr)return 0;
	auto AmmoType = EquippedWeapon->GetAmmoType();

	if (AmmoMap.Contains(AmmoType)) {
		return AmmoMap[AmmoType] > 0;
	}


	return false;
}

void AShooterCharacter::FinishReloading() {

	CombatState = ECombatState::ECS_UnOccupied;

	if (EquippedWeapon == nullptr)return;
	const auto AmmoType{ EquippedWeapon->GetAmmoType()};
	if (AmmoMap.Contains(AmmoType)) {
		int32 CarriedAmmo = AmmoMap[AmmoType];

		const int32 MagEmptySpace = EquippedWeapon->GetMagazineCapacity() - EquippedWeapon->GetAmmo();
		if (MagEmptySpace > CarriedAmmo) {
			EquippedWeapon->ReloadAmmo(CarriedAmmo);
			CarriedAmmo = 0;
			AmmoMap.Add(AmmoType, CarriedAmmo);
		}
		else {
			EquippedWeapon->ReloadAmmo(MagEmptySpace);
			CarriedAmmo -= MagEmptySpace;
			AmmoMap.Add(AmmoType, CarriedAmmo);
		}

	}






}







UAbilitySystemComponent* AShooterCharacter::GetAbilitySystemComponent() const {
	return AbilitySystemComp;
}






void AShooterCharacter::AquireAbility(TSubclassOf<UGameplayAbility> AbilityToAquire) {

	if (AbilitySystemComp) {
		if (HasAuthority()&&AbilityToAquire) {
			FGameplayAbilitySpecDef SpecDef = FGameplayAbilitySpecDef();
			SpecDef.Ability = AbilityToAquire;
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(SpecDef, 1);
			AbilitySystemComp->GiveAbility(AbilitySpec);

		}
		AbilitySystemComp->InitAbilityActorInfo(this, this);
	}




}

bool AShooterCharacter::IsOtherHostile(AShooterCharacter* Other) {
	return TeamId!=Other->GetTeamID();
}

uint8 AShooterCharacter::GetTeamID() const {
	return TeamId;
}

float AShooterCharacter::GetCrosshairSpreadMultipler() const {
	return CrosshairSpreadMultiplier;
}

void AShooterCharacter::IncrementOverlappedItemCount(int8 Amount) {

	if (OverlappedItemCount + Amount <= 0) {


		OverlappedItemCount = 0;
		bShouldTraceForItems = 0;

	}
	else {
		OverlappedItemCount += Amount;
		bShouldTraceForItems = 1;

	}

}

FVector AShooterCharacter::GetCameraInterpLocation() {
	
	const FVector CameraWorldLocation = FollowCamera->GetComponentLocation();
	const FVector CameraForward = FollowCamera->GetForwardVector();

	
	return CameraWorldLocation+CameraForward*CameraInterpDistance+FVector(0.f,0.f,CameraInterpElevation);
}

void AShooterCharacter::GetPickupItem(AItem* Item) {

	if (Item->GetEquipSound()) {
		UGameplayStatics::PlaySound2D(this, Item->GetEquipSound());
	}


	auto Weapon = Cast<AWeapon>(Item);
	if (Weapon) {
		SwapWeapon(Weapon);
	}

	auto Ammo = Cast<AAmmo>(Item);
	if(Ammo)
	PickupAmmo( Ammo);


}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CameraInterpZoom(DeltaTime);
	CalculateCrosshairSpread(DeltaTime);

	TraceForItems();

	


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

	PlayerInputComponent->BindAction("Select", IE_Pressed, this, &AShooterCharacter::SelectButtonPressed);
	PlayerInputComponent->BindAction("Select", IE_Released, this, &AShooterCharacter::SelectButtonReleased);

	PlayerInputComponent->BindAction("ReloadButton", IE_Pressed, this, &AShooterCharacter::ReloadButtonPressed);

	PlayerInputComponent->BindAction("OneKey", IE_Pressed, this, &AShooterCharacter::OneKeyPressed);



}

