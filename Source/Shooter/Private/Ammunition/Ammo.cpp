// Ultimate Apex Shooter.All Rights Reserved..


#include "Ammunition/Ammo.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/SphereComponent.h"
#include "Character/ShooterCharacter.h"



AAmmo::AAmmo() {
	AmmoMesh = CreateDefaultSubobject<UStaticMeshComponent>("AmmoMesh");
	SetRootComponent(AmmoMesh);

	GetCollisionBox()->SetupAttachment(GetRootComponent());
	GetAreaSphere()->SetupAttachment(GetRootComponent());
	GetPickupWidget()->SetupAttachment(GetRootComponent());


	AmmoCollisionSphere = CreateDefaultSubobject<USphereComponent>("AmmoCollisionSphere");
	AmmoCollisionSphere->SetupAttachment(GetRootComponent());
	AmmoCollisionSphere->SetSphereRadius(100.f);


}

void AAmmo::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);



}

void AAmmo::BeginPlay() {

	Super::BeginPlay();

	AmmoCollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AAmmo::AmmoSphereOverlap);

}

void AAmmo::SetItemProperties(EItemState State) {

	Super::SetItemProperties(State);

	switch (State) {
	case EItemState::EIS_Pickup:
		AmmoMesh->SetSimulatePhysics(0);
		AmmoMesh->SetEnableGravity(0);
		AmmoMesh->SetVisibility(1);
		AmmoMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		AmmoMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		

		
		break;
	case EItemState::EIS_EquipInterping:
		
		AmmoMesh->SetSimulatePhysics(0);
		AmmoMesh->SetEnableGravity(0);
		AmmoMesh->SetVisibility(1);
		AmmoMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		AmmoMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	




		break;
	case EItemState::EIS_PickedUp:
		break;
	case EItemState::EIS_Equipped:

		
		AmmoMesh->SetSimulatePhysics(0);
		AmmoMesh->SetEnableGravity(0);
		AmmoMesh->SetVisibility(1);
		AmmoMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		AmmoMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		

		


		break;
	case EItemState::EIS_Falling:

		AmmoMesh->SetSimulatePhysics(1);
		AmmoMesh->SetEnableGravity(1);
		AmmoMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		AmmoMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		AmmoMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);

		
		



		break;
	case EItemState::EIS_MAX:
		break;
	default:
		break;
	}



}

void AAmmo::AmmoSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

	if (OtherActor) {
		auto OverlappedCharacter = Cast<AShooterCharacter>(OtherActor);
		if (OverlappedCharacter) {
			StartItemCurve(OverlappedCharacter);
			AmmoCollisionSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	
	
	
	}




}

void AAmmo::EnableCustomDepth() {

	AmmoMesh->SetRenderCustomDepth(1);
}

void AAmmo::DisableCustomDepth() {

	AmmoMesh->SetRenderCustomDepth(0);
}


