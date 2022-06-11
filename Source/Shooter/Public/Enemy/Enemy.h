// Ultimate Apex Shooter.All Rights Reserved..

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/BulletHitInterface.h"
#include "Enemy.generated.h"

UCLASS()
class SHOOTER_API AEnemy : public ACharacter,public IBulletHitInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
		class UParticleSystem* ImpactParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
		class USoundCue* ImpactSound;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		float Health=100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health, meta = (AllowPrivateAccess = "true"))
		float MaxHealth=100.f;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BulletHit_Implementation(FHitResult HitResult) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;





};
