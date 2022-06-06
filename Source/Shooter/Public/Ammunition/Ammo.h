// Ultimate Apex Shooter.All Rights Reserved..

#pragma once

#include "CoreMinimal.h"
#include "Weapons/Item.h"
#include "AmmoTypes.h"
#include "Ammo.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API AAmmo : public AItem
{
	GENERATED_BODY()
	


public:
	AAmmo();

	virtual void Tick(float DeltaTime) override;

	virtual void EnableCustomDepth() override;
	virtual void DisableCustomDepth() override;

protected:

	virtual void BeginPlay() override;

	virtual void SetItemProperties(EItemState State) override;

	UFUNCTION()
	void AmmoSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	



private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ammo, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* AmmoMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ammo, meta = (AllowPrivateAccess = "true"))
		EAmmoType AmmoType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ammo, meta = (AllowPrivateAccess = "true"))
		class USphereComponent* AmmoCollisionSphere;

public:

	FORCEINLINE UStaticMeshComponent* GetAmmoMesh() const { return AmmoMesh; }


	FORCEINLINE EAmmoType GetAmmoType() const { return AmmoType; }




};
