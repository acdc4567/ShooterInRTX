// Ultimate Apex Shooter.All Rights Reserved..

#pragma once

#include "CoreMinimal.h"
#include "Weapons/Item.h"
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


protected:

	virtual void BeginPlay() override;

	virtual void SetItemProperties(EItemState State) override;


private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ammo, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* AmmoMesh;

public:

	FORCEINLINE UStaticMeshComponent* GetAmmoMesh() const { return AmmoMesh; }






};
