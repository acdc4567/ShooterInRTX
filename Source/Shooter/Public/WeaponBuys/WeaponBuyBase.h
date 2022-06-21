// Ultimate Apex Shooter.All Rights Reserved..

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TPS_Enums.h"
#include "WeaponBuyBase.generated.h"

UCLASS()
class SHOOTER_API AWeaponBuyBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBuyBase();


	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
		class UStaticMeshComponent* StaticGunMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Components)
		class USphereComponent* AreaSphere;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Components)
		class URotatingMovementComponent* RotatingMovement;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Components)
		FName WeaponName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Components)
		int32 WeaponCost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Components)
		TSubclassOf<class ATPS_BaseWeapon> WeaponClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
		class ATPS_Character* TPS_Character;








	//Functions

	UFUNCTION()
		void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);






public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE TSubclassOf<class ATPS_BaseWeapon> GetWeaponClass() const { return WeaponClass; }



};
