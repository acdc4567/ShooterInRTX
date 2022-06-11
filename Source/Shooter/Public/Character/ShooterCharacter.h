// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AmmoTypes.h"
#include "ShooterCharacter.generated.h"




UENUM(BlueprintType)
enum class ECombatState :uint8 {
	ECS_UnOccupied UMETA(DisplayName = "UnOccupied")
	, ECS_FireTimerInProgress UMETA(DisplayName = "FireTimerInProgress")
	, ECS_Reloading UMETA(DisplayName = "Reloading")

	, ECS_MAX UMETA(DisplayName = "DefaultMAX")

};


UCLASS()
class SHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();


	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UFUNCTION(BlueprintCallable)
		void FinishReloading();


protected:


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);

	void MoveRight(float Value);

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);

	void MouseTurn(float Value);

	void MouseLookUp(float Value);

	void FireWeapon();

	bool GetBeamEndLocation(const FVector& MuzzleSocketLocation, FHitResult& OutHitResult);

	void AimingButtonPressed();
	void AimingButtonReleased();

	void CameraInterpZoom(float DeltaTime);

	void CalculateCrosshairSpread(float DeltaTime);


	void FireButtonPressed();
	void FireButtonReleased();


	void StartFireTimer();

	UFUNCTION()
	void AutoFireReset();

	bool TraceUnderCrosshairs(FHitResult& OutHitResult,FVector & OutHitLocation);

	void TraceForItems();

	class AWeapon*  SpawnDefaultWeapon();

	void EquipWeapon(AWeapon*  WeaponToEquip);

	void DropWeapon();

	void SelectButtonPressed();
	void SelectButtonReleased();

	void SwapWeapon(AWeapon* WeaponToSwap);

	void InitializeAmmoMap();

	bool WeaponHasAmmo();


	void PlayFireSound();
	void SendBullet();
	void PlayGunFireMontage();

	void ReloadButtonPressed();

	void ReloadWeapon();

	
	bool CarryingAmmo();

	void PickupAmmo(class AAmmo* Ammo);





private:

	//VisibleAnywhere,BlueprintReadOnly,Category=Camera,meta=(AllowPrivateAccess="true")
	//EditAnywhere,BlueprintReadWrite,Category=Camera,meta=(AllowPrivateAccess="true")




	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category=Camera,meta=(AllowPrivateAccess="true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		float BaseTurnRate=45.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		float BaseLookUpRate=45.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
		class USoundCue* FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
		 USoundCue* TwinFireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
		class UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
		bool bIsCarryingTwinBlast=1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* HipFireMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
		 UAnimMontage* BelicaHipFireMontage;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
		 UParticleSystem* ImpactParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
		UParticleSystem* BeamParticles;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
		bool bAiming=0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		float CameraDefaultFOV =0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		float CameraZoomedFOV=60.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		float CameraCurrentFOV=0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		float ZoomInterpSpeed = 20.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		float HipTurnRate=.8f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		float HipLookUpRate=.8f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		float AimTurnRate=.6f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		float AimLookUpRate=.6f;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		float CrosshairSpreadMultiplier;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		float CrosshairVelocityFactor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		float CrosshairInAirFactor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		float CrosshairAimFactor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		float CrosshairShootingFactor;

	bool bFireButtonPressed=0;

	bool bShouldFire=1;

	float AutomaticFireRate = .1f;
	
	
	FTimerHandle AutoFireTimer;

	bool bShouldTraceForItems=0;
	
	int8 OverlappedItemCount = 0;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Items, meta = (AllowPrivateAccess = "true"))
		class AItem* TraceHitItemLastFrame;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
		 AWeapon* EquippedWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AWeapon> DefaultWeaponClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
		AItem* TraceHitItem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Items, meta = (AllowPrivateAccess = "true"))
		float CameraInterpDistance=250.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Items, meta = (AllowPrivateAccess = "true"))
		float CameraInterpElevation=65.f;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Items, meta = (AllowPrivateAccess = "true"))
		TMap<EAmmoType, int32> AmmoMap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Items, meta = (AllowPrivateAccess = "true"))
		int32 Starting9mmAmmo=85;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Items, meta = (AllowPrivateAccess = "true"))
		int32 StartingARAmmo=120;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
		USceneComponent* LHandSceneComponent;

	FTransform ClipTransform;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat, meta = (AllowPrivateAccess = "true"))
		ECombatState CombatState=ECombatState::ECS_UnOccupied;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
		UAnimMontage* ReloadMontage;


public:

	
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	FORCEINLINE bool GetIsCarryingTwinBlast() const { return bIsCarryingTwinBlast; }
	FORCEINLINE bool GetAiming() const { return bAiming; }

	UFUNCTION(BlueprintCallable)
	 float GetCrosshairSpreadMultipler() const;

	FORCEINLINE int8 GetOverlappedItemCount() const { return OverlappedItemCount; }

	void IncrementOverlappedItemCount(int8 Amount);

	FVector GetCameraInterpLocation();

	void GetPickupItem(AItem* Item);

	FORCEINLINE ECombatState GetCombatState() const { return CombatState; }








};
