// Ultimate Apex Shooter.All Rights Reserved..

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBaseWeapon.generated.h"

UCLASS()
class SHOOTER_API ASTUBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTUBaseWeapon();

	virtual void StartFire();
	virtual void StopFire();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
		class USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
		FName MuzzleSocketName = FName("MuzzleFlash");


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
		float TraceMaxDistance = 80000.f;

	
	

	virtual void MakeShot();


	ACharacter* GetPlayerCharacter() const;

	APlayerController* GetPlayerController() const;

	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;

	FVector GetMuzzleWorldLocation() const;

	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

	void MakeHit(FHitResult& HitResult,const FVector& TraceStart, const FVector& TraceEnd);

	
private:


	
	
	

public:	
	

};
