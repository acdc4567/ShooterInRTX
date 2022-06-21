// Ultimate Apex Shooter.All Rights Reserved..


#include "WeaponBuys/WeaponBuyBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Weapons/TPS_BaseWeapon.h"
#include "Character/TPS_Character.h"




// Sets default values
AWeaponBuyBase::AWeaponBuyBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticGunMesh = CreateDefaultSubobject<UStaticMeshComponent>("GunMesh");
	StaticGunMesh->SetupAttachment(GetRootComponent());

	AreaSphere = CreateDefaultSubobject<USphereComponent>("OverlapSphere");
	AreaSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	AreaSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	AreaSphere->SetupAttachment(GetRootComponent());

	RotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>("RotatingMovement");



}

// Called when the game starts or when spawned
void AWeaponBuyBase::BeginPlay()
{
	Super::BeginPlay();
	
	AreaSphere->OnComponentBeginOverlap.AddDynamic(this, &AWeaponBuyBase::OnSphereOverlap);
	AreaSphere->OnComponentEndOverlap.AddDynamic(this, &AWeaponBuyBase::OnSphereEndOverlap);




}

void AWeaponBuyBase::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (OtherActor) {
		ATPS_Character*  TPS_Characterx = Cast<ATPS_Character>(OtherActor);
		if (TPS_Characterx) {
			//TPS_Character->EquipWeapon(TPS_Character->SpawnWeapon(WeaponClass));
			TPS_Characterx->IncrementOverlappedItemCount(this);

		}

	}


}

void AWeaponBuyBase::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	if (OtherActor) {
		ATPS_Character* TPS_Characterx = Cast<ATPS_Character>(OtherActor);
		if (TPS_Characterx) {
			//TPS_Character->EquipWeapon(TPS_Character->SpawnWeapon(WeaponClass));
			TPS_Characterx->IncrementOverlappedItemCount(nullptr);

		}

	}

	



}

// Called every frame
void AWeaponBuyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

