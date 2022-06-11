// Ultimate Apex Shooter.All Rights Reserved..

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUDevDamageActor.generated.h"

UCLASS()
class SHOOTER_API ASTUDevDamageActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTUDevDamageActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Radius = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Damage = .1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MinDamage = .05f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FColor SphereColor = FColor::Red;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DamageInnerRadius = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DamageOuterRadius = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DamageFalloff = 3.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UDamageType> DamageTypeClass;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
