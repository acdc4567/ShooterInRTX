// Ultimate Apex Shooter.All Rights Reserved..

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STUBaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;




UCLASS()
class SHOOTER_API ASTUBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASTUBaseCharacter(const	 FObjectInitializer& ObjInit);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		UCameraComponent* CameraComponent;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		class USTUHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		class USTUWeaponComponent* WeaponComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		class UTextRenderComponent* HealthTextComponent;

	void TakeDamagePressed();

	UPROPERTY(EditAnywhere,  Category = Animation)
		UAnimMontage* DeathAnimMontage;

	UPROPERTY(EditAnywhere,  Category = Movement)
		FVector2D LandedDamageVelocity=FVector2D(900.f,1200.f);

	UPROPERTY(EditAnywhere, Category = Movement)
		FVector2D LandedDamage= FVector2D(10.f, 50.f);

	





private:
	bool bWantsToRun = 0;
	bool bIsMovingForward = 0;



	void MoveForward(float Amount);
	void MoveRight(float Amount);

	void LookUp(float Amount);
	void TurnAround(float Amount);

	void OnStartRunning();
	void OnStopRunning();

	void OnDeath();

	void OnHealthChanged(float Health);

	UFUNCTION()
		void OnGroundLanded(const FHitResult& Hit);

	



public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UFUNCTION(BlueprintCallable, Category = "Movement")
		bool IsRunning() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
		float GetMovementDirection() const;

	FORCEINLINE USpringArmComponent* GetSpringArm() const { return SpringArmComponent; }


};
