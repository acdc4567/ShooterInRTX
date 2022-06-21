// Ultimate Apex Shooter.All Rights Reserved..

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUProjectile.generated.h"

UCLASS()
class SHOOTER_API ASTUProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTUProjectile();

	void SetShotDirection(const FVector& Direction);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
		class USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
		class UProjectileMovementComponent* MovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Components)
		float DamageRadius = 200.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Components)
		float DamageInnerRadius = 100.f;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Components)
		float DamageFalloff = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Components)
		float DamageAmount = 50.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Components)
		float MinDamageAmount = 25.f;

	UFUNCTION()
		void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Components)
		UParticleSystem* ImpactParticles;

private:

	FVector ShotDirection;


	AController* GetController() const;


public:	
	

};
