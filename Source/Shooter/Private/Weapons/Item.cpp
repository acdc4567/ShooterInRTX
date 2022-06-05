// Ultimate Apex Shooter.All Rights Reserved..


#include "Weapons/Item.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/SphereComponent.h"
#include "Character/ShooterCharacter.h"
#include "Curves/CurveFloat.h"
#include "Camera/CameraComponent.h"
#include "Sound/SoundCue.h"




// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<USkeletalMeshComponent>("ItemMesh");
	SetRootComponent(ItemMesh);

	ItemMeshx2 = CreateDefaultSubobject<USkeletalMeshComponent>("ItemMeshx2");
	ItemMeshx2->SetupAttachment(ItemMesh);
	ItemMeshx2->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);


	CollisionBox = CreateDefaultSubobject<UBoxComponent>("CollisionBox");
	CollisionBox->SetupAttachment(ItemMesh);
	CollisionBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CollisionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);



	PickupWidget = CreateDefaultSubobject<UWidgetComponent>("PickupWidget");
	PickupWidget->SetupAttachment(GetRootComponent());

	AreaSphere = CreateDefaultSubobject<USphereComponent>("AreaSphere");
	AreaSphere->SetupAttachment(GetRootComponent());





}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	

	PickupWidget->SetVisibility(0);


	AreaSphere->OnComponentBeginOverlap.AddDynamic(this,&AItem::OnSphereOverlap);
	AreaSphere->OnComponentEndOverlap.AddDynamic(this, &AItem::OnSphereEndOverlap);

	SetItemProperties(ItemState);



}

void AItem::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

	if (OtherActor) {
		AShooterCharacter* ShooterCharacter = Cast<AShooterCharacter>(OtherActor);
		if (ShooterCharacter) {
			ShooterCharacter->IncrementOverlappedItemCount(1);
		}

	}


}

void AItem::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {

	if (OtherActor) {
		AShooterCharacter* ShooterCharacter = Cast<AShooterCharacter>(OtherActor);
		if (ShooterCharacter) {
			ShooterCharacter->IncrementOverlappedItemCount(-1);
		}

	}


}

void AItem::SetItemProperties(EItemState State) {

	switch (State) {
	case EItemState::EIS_Pickup:
		ItemMesh->SetSimulatePhysics(0);
		ItemMesh->SetEnableGravity(0);
		ItemMesh->SetVisibility(1);
		ItemMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		ItemMeshx2->SetSimulatePhysics(0);
		ItemMeshx2->SetEnableGravity(0);
		ItemMeshx2->SetVisibility(0);
		ItemMeshx2->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		ItemMeshx2->SetCollisionEnabled(ECollisionEnabled::NoCollision);


		AreaSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
		AreaSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		
		CollisionBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		CollisionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
		CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		break;
	case EItemState::EIS_EquipInterping:
		PickupWidget->SetVisibility(0);

		ItemMesh->SetSimulatePhysics(0);
		ItemMesh->SetEnableGravity(0);
		ItemMesh->SetVisibility(1);
		ItemMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		ItemMeshx2->SetSimulatePhysics(0);
		ItemMeshx2->SetEnableGravity(0);
		ItemMeshx2->SetVisibility(0);
		ItemMeshx2->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		ItemMeshx2->SetCollisionEnabled(ECollisionEnabled::NoCollision);


		AreaSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		AreaSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		CollisionBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		CollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);





		break;
	case EItemState::EIS_PickedUp:
		break;
	case EItemState::EIS_Equipped:

		PickupWidget->SetVisibility(0);

		ItemMesh->SetSimulatePhysics(0);
		ItemMesh->SetEnableGravity(0);
		ItemMesh->SetVisibility(1);
		ItemMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		ItemMeshx2->SetSimulatePhysics(0);
		ItemMeshx2->SetEnableGravity(0);
		ItemMeshx2->SetVisibility(1);
		ItemMeshx2->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		ItemMeshx2->SetCollisionEnabled(ECollisionEnabled::NoCollision);


		AreaSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		AreaSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		CollisionBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		CollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);



		break;
	case EItemState::EIS_Falling:

		ItemMesh->SetSimulatePhysics(1);
		ItemMesh->SetEnableGravity(1);
		ItemMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		ItemMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		ItemMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);

		ItemMeshx2->SetSimulatePhysics(1);
		ItemMeshx2->SetEnableGravity(1);
		ItemMeshx2->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		ItemMeshx2->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		ItemMeshx2->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
		ItemMeshx2->SetVisibility(0);

		AreaSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		AreaSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		CollisionBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		CollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);





		break;
	case EItemState::EIS_MAX:
		break;
	default:
		break;
	}
}

void AItem::FinishInterping() {
	bInterping = 0;
	if (Character) {
		Character->GetPickupItem(this);
	}
	SetActorScale3D(FVector(1.f));


}

void AItem::ItemInterp(float DeltaTime) {

	if (!bInterping) {
		return;

	}
	if (Character&&ItemZCurve) {
		const float ElapsedTime = GetWorldTimerManager().GetTimerElapsed(ItemInterpTimer);
	
		const float CurveValue = ItemZCurve->GetFloatValue(ElapsedTime);
		FVector ItemLocation = ItemInterpStartLocation;
		const FVector CameraInterpLocation = Character->GetCameraInterpLocation();
		const FVector ItemToCamera = FVector(0.f,0.f,(CameraInterpLocation-ItemLocation).Z);
		const float DeltaZ = ItemToCamera.Size();

		const FVector CurrentLocation=GetActorLocation();
		const float InterpXValue=FMath::FInterpTo(CurrentLocation.X,CameraInterpLocation.X,DeltaTime,30.f);
		const float InterpYValue = FMath::FInterpTo(CurrentLocation.Y, CameraInterpLocation.Y, DeltaTime, 30.f);



		ItemLocation.X = InterpXValue;
		ItemLocation.Y = InterpYValue;
		ItemLocation.Z += CurveValue * DeltaZ;
		SetActorLocation(ItemLocation, 1, nullptr, ETeleportType::TeleportPhysics);
	
		const FRotator CameraRotation = Character->GetFollowCamera()->GetComponentRotation();
		FRotator ItemRotation{ 0.f,CameraRotation.Yaw + InterpInitialYawOffset,0.f };
		SetActorRotation(ItemRotation, ETeleportType::TeleportPhysics);
		if (ItemScaleCurve) {
			const float ScaleCurveValue =  ItemScaleCurve->GetFloatValue(ElapsedTime);
			SetActorScale3D(FVector(ScaleCurveValue));
		}
		

	}




}

void AItem::SetItemState(EItemState State) {
	ItemState = State;
	SetItemProperties(State);

}

void AItem::StartItemCurve(AShooterCharacter* Char) {
	Character = Char;

	ItemInterpStartLocation = GetActorLocation();
	bInterping = 1;
	SetItemState(EItemState::EIS_EquipInterping);
	GetWorldTimerManager().SetTimer(ItemInterpTimer, this, &AItem::FinishInterping,ZCurveTime);

	const float CameraRotationYaw = Character->GetFollowCamera()->GetComponentRotation().Yaw;
	const float ItemRotationYaw = GetActorRotation().Yaw;
	InterpInitialYawOffset = ItemRotationYaw - CameraRotationYaw;
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ItemInterp(DeltaTime);
}

