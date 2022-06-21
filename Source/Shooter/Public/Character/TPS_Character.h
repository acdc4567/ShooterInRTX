// Ultimate Apex Shooter.All Rights Reserved..

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TPS_Enums.h"
#include "TPS_Character.generated.h"

UCLASS()
class SHOOTER_API ATPS_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATPS_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Components")
	//UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Components")

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
		float MouseHipTurnRate = .7f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
		float MouseHipLookUpRate = .7f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		class USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		class ATPS_BaseWeapon* CurrentWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		 ATPS_BaseWeapon* WeaponSlot_01;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		 ATPS_BaseWeapon* WeaponSlot_02;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
		TSubclassOf< ATPS_BaseWeapon> DefaultWeaponClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
		UAnimMontage* HipFireMontage;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		bool bCanFire=1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		bool bIsFiring = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		bool bIsReloading = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		bool bIsChangingWeapon = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		int32 OverlappedItemCount = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		EHasWeapon HasWeaponEnum = EHasWeapon::EHW_NoWeapon;

	FOnInteract OnInteract;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
		class AWeaponBuyBase* ItemNearby;






	//Functions

	void TurnAround(float Value);
	void LookUp(float Value);

	void MoveForward(float Value);
	void MoveRight(float Value);

	void EquipWeapon(ATPS_BaseWeapon* Weapon);

	ATPS_BaseWeapon* SpawnWeapon(TSubclassOf<ATPS_BaseWeapon> WeaponClass);

	void ShowWeapon(ATPS_BaseWeapon* WeaponToShow);
	
	void OneKeyPressed();

	void StartFire();
	void StopFire();

	void SelectButtonPressed();
	
	void DropWeapon();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE USpringArmComponent* GetSpringArm() const { return SpringArmComponent; }

	UFUNCTION(BlueprintCallable, Category = "Movement")
		float GetMovementDirection() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
		EWeaponxTypes GetCurrentWeaponType() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
		bool GetIsFiring() const;

	void PlayGunFireMontage();

	void IncrementOverlappedItemCount( AWeaponBuyBase* WeaponBuy);





};
