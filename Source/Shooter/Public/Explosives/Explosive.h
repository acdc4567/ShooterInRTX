// Ultimate Apex Shooter.All Rights Reserved..

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/BulletHitInterface.h"
#include "Explosive.generated.h"

UCLASS()
class SHOOTER_API AExplosive : public AActor,public IBulletHitInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExplosive();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
		class UParticleSystem* ExplodeParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
		class USoundCue* ExplodeSound;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void BulletHit_Implementation(FHitResult HitResult) override;

};
