// Ultimate Apex Shooter.All Rights Reserved..


#include "Weapons/STUProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"





// Sets default values
ASTUProjectile::ASTUProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = 0;


	CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
	CollisionComponent->InitSphereRadius(5.f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	SetRootComponent(CollisionComponent);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");;
	MovementComponent->InitialSpeed = 15000.f;
	MovementComponent->ProjectileGravityScale = .76f;




}

void ASTUProjectile::SetShotDirection(const FVector& Direction) {

	ShotDirection = Direction;




}

// Called when the game starts or when spawned
void ASTUProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	check(MovementComponent);
	check(CollisionComponent);
	MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;
	CollisionComponent->IgnoreActorWhenMoving(GetOwner(), 1);
	CollisionComponent->OnComponentHit.AddDynamic(this, &ASTUProjectile::OnProjectileHit);


	SetLifeSpan(5.f);

}

void ASTUProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {

	if (!GetWorld())return;
	MovementComponent->StopMovementImmediately();

	UGameplayStatics::ApplyRadialDamageWithFalloff(GetWorld(), DamageAmount, MinDamageAmount, GetActorLocation(), DamageInnerRadius, DamageRadius, DamageFalloff, UDamageType::StaticClass(), {GetOwner()}, this, GetController(), ECollisionChannel::ECC_Visibility);

	DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadius, 24, FColor::Red,0,5.f);
	Destroy();

}

AController* ASTUProjectile::GetController() const {
	const auto Pawn = Cast<APawn>(GetOwner());
	return Pawn ? Pawn->GetController() : nullptr;
}



