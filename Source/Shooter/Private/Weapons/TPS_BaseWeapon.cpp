// Ultimate Apex Shooter.All Rights Reserved..


#include "Weapons/TPS_BaseWeapon.h"
#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "DrawDebugHelpers.h"
#include "Character/TPS_Character.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Interfaces/TakeDamage.h"



// Sets default values
ATPS_BaseWeapon::ATPS_BaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>("GunMesh");
	GunMesh->SetupAttachment(SceneComponent);






}

// Called when the game starts or when spawned
void ATPS_BaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	check(GunMesh);

	TPSCharacterx = Cast<ATPS_Character>(GetOwner());


}


void ATPS_BaseWeapon::MakeShot() {





	if (!GetWorld() ) {
		StopFire();
		return;
	}

	if (!BeamParticles) {
		StopFire();
		return;
	}

	FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd)) {
		StopFire();
		return;
	}

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	
	if (MuzzleParticles) {
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleParticles, GetMuzzleWorldLocation());

	}



	if (HitResult.bBlockingHit) {
		//MakeDamage(HitResult);
		//DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Cyan, 0, 3.f, 0, 3.f);
		
		if (ImpactParticles) {
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticles, HitResult.ImpactPoint);

		}
		UParticleSystemComponent* Beam = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BeamParticles, GetMuzzleWorldLocation());

		if (Beam) {
			Beam->SetVectorParameter(FName("Target"), HitResult.ImpactPoint);
		}
		//DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.f, 24, FColor::Red, 0, 5.f);
		AddDamage(HitResult);





	}
	else {
		//DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Green, 0, 3.f, 0, 3.f);
		UParticleSystemComponent* Beam = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BeamParticles, GetMuzzleWorldLocation());
		
		if (Beam) {
			Beam->SetVectorParameter(FName("Target"), TraceEnd);
		}
	}







}

void ATPS_BaseWeapon::AddDamage(const FHitResult& HitResult) {
	if (HitResult.GetActor()) {
		ITakeDamage* TakeDamageInterface = Cast<ITakeDamage>(HitResult.GetActor());
		if (TakeDamageInterface) {
			TakeDamageInterface->TakeDamage_Implementation(Damage,CriticalHitDamageModifier,HitResult);
		}

	}

}










ACharacter* ATPS_BaseWeapon::GetPlayerCharacter() const {
	return Cast<ACharacter>(GetOwner());
}

APlayerController* ATPS_BaseWeapon::GetPlayerController() const {
	const auto Player = GetPlayerCharacter();
	if (!Player)return nullptr;


	return Player->GetController<APlayerController>();
}



FVector ATPS_BaseWeapon::GetMuzzleWorldLocation() const {
	return GunMesh->GetSocketLocation(MuzzleSocketName);
}







bool ATPS_BaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const {
	FVector ViewLocation;
	FRotator ViewRotation;
	if (!GetPlayerViewPoint(ViewLocation, ViewRotation))return 0;

	const auto TPSPlayer = Cast<ATPS_Character>(GetPlayerCharacter());
	if (!TPSPlayer)return 0;

	const auto SpringArmDistance = TPSPlayer->GetSpringArm()->TargetArmLength + 100.f;
	FVector ShootDirection = ViewRotation.Vector();
	TraceStart = ViewLocation + ShootDirection * SpringArmDistance;
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
	return 1;


}


bool ATPS_BaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const {

	const auto TPSCharacter = Cast<ACharacter>(GetOwner());
	if (!TPSCharacter)return 0;

	if (TPSCharacter->IsPlayerControlled()) {

		const auto Controller = GetPlayerController();
		if (!Controller)return 0;

		Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);


	}
	else {
		/*
		const auto STUAICharacter = Cast<ASTUAICharacter>(GetOwner());
		if (STUAICharacter) {
			//UE_LOG(LogBaseWeapon, Warning, TEXT("AICharacterCast"));
			const auto Controller = Cast<ASTUAIController>(STUAICharacter->GetController());
			if (Controller) {
				//UE_LOG(LogBaseWeapon, Warning, TEXT("AIControllerrCast"));
				ViewLocation = GetMuzzleWorldLocation();
				ViewRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Controller->GetFocalPoint());



			}
		}

		else {
			ViewLocation = GetMuzzleWorldLocation();
			ViewRotation = STUCharacter->GetActorRotation();
		}*/



	}




	return 1;
}



void ATPS_BaseWeapon::StartFire() {

	GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ATPS_BaseWeapon::MakeShot, TimeBetweenShots, 1);
	MakeShot();
	
	

}

void ATPS_BaseWeapon::StopFire() {
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);

}


void ATPS_BaseWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd) {
	if (!GetWorld())return;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());


	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);



}


// Called every frame
void ATPS_BaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

