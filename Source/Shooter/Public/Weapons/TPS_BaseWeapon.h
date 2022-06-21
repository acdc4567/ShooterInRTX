// Ultimate Apex Shooter.All Rights Reserved..

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TPS_Enums.h"
#include "TPS_BaseWeapon.generated.h"

UCLASS()
class SHOOTER_API ATPS_BaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATPS_BaseWeapon();


	virtual void StartFire();
	virtual void StopFire();







protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		class USceneComponent* SceneComponent;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		class USkeletalMeshComponent* GunMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
		FName SocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
		FName MuzzleSocketName="MuzzleFlash";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
		EWeaponxTypes WeaponType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
		float TimeBetweenShots = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
		float TraceMaxDistance=80000.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Components)
		float Damage = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Components)
		float CriticalHitDamageModifier = 1.2f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Components)
		UParticleSystem* ImpactParticles;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Components)
		UParticleSystem* MuzzleParticles;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Components)
		UParticleSystem* BeamParticles;


	//Functions

	void MakeShot();

	ACharacter* GetPlayerCharacter() const;

	APlayerController* GetPlayerController() const;

	FVector GetMuzzleWorldLocation() const;

	bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;

	void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);

	void AddDamage(const FHitResult& HitResult);





private:

	FTimerHandle ShotTimerHandle;

	class ATPS_Character* TPSCharacterx;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE EWeaponxTypes GetWeaponType() const { return WeaponType; }

	FORCEINLINE FName GetSocketName() const { return SocketName; }

	FORCEINLINE USkeletalMeshComponent* GetGunMesh() const { return GunMesh; }







};
