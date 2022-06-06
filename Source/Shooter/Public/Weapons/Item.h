// Ultimate Apex Shooter.All Rights Reserved..

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"


UENUM(BlueprintType)
enum class EItemRarity :uint8 {
	EIR_Damaged UMETA(DisplayName="Damaged")
	, EIR_Common UMETA(DisplayName = "Common")
	, EIR_UnCommon UMETA(DisplayName = "UnCommon")
	, EIR_Rare UMETA(DisplayName = "Rare")
	, EIR_Legendary UMETA(DisplayName = "Legendary")
	, EIR_MAX UMETA(DisplayName = "DefaultMAX")

};

UENUM(BlueprintType)
enum class EItemType : uint8 {
	EIT_Ammo UMETA(DisplayName = "Ammo"),
	EIT_Weapon UMETA(DisplayName = "Weapon"),

	EIT_MAX UMETA(DisplayName = "DefaultMAX")
};

UENUM(BlueprintType)
enum class EItemState :uint8 {
	EIS_Pickup UMETA(DisplayName = "Pickup")
	, EIS_EquipInterping UMETA(DisplayName = "EquipInterping")
	, EIS_PickedUp UMETA(DisplayName = "PickedUp")
	, EIS_Equipped UMETA(DisplayName = "Equipped")
	, EIS_Falling UMETA(DisplayName = "Falling")
	, EIS_MAX UMETA(DisplayName = "DefaultMAX")

};

UCLASS()
class SHOOTER_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void EnableCustomDepth();
	virtual void DisableCustomDepth();
	void DIsableGlowMaterial();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	virtual void SetItemProperties(EItemState State);

	void FinishInterping();

	void ItemInterp(float DeltaTime);

	
	virtual void InitializeCustomDepth();


	virtual void OnConstruction(const FTransform & Transform) override;

	void EnableGlowMaterial();
	
	void UpdatePulse();

	void StartPulseTimer();
	void ResetPulseTimer();


private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ItemProperties, meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* ItemMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ItemProperties, meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* ItemMeshx2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ItemProperties, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ItemProperties, meta = (AllowPrivateAccess = "true"))
		class UWidgetComponent* PickupWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ItemProperties, meta = (AllowPrivateAccess = "true"))
		class USphereComponent* AreaSphere;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ItemProperties, meta = (AllowPrivateAccess = "true"))
		FString ItemName=FString("Default");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemProperties, meta = (AllowPrivateAccess = "true"))
		int32 ItemCount=0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ItemProperties, meta = (AllowPrivateAccess = "true"))
		EItemRarity ItemRarity=EItemRarity::EIR_Common;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ItemProperties, meta = (AllowPrivateAccess = "true"))
		EItemState ItemState = EItemState::EIS_Pickup;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ItemProperties, meta = (AllowPrivateAccess = "true"))
		bool bIsTwinBlast = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ItemProperties, meta = (AllowPrivateAccess = "true"))
		class UCurveFloat* ItemZCurve;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ItemProperties, meta = (AllowPrivateAccess = "true"))
		FVector ItemInterpStartLocation=FVector(0.f);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ItemProperties, meta = (AllowPrivateAccess = "true"))
		FVector CameraTargetLocation=FVector(0.f);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ItemProperties, meta = (AllowPrivateAccess = "true"))
		bool bInterping=0;

	FTimerHandle ItemInterpTimer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ItemProperties, meta = (AllowPrivateAccess = "true"))
		float ZCurveTime=.7f;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ItemProperties, meta = (AllowPrivateAccess = "true"))
		class AShooterCharacter* Character;

	float ItemInterpX=0.f;
	float ItemInterpY=0.f;

	float InterpInitialYawOffset=0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ItemProperties, meta = (AllowPrivateAccess = "true"))
		UCurveFloat* ItemScaleCurve;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ItemProperties, meta = (AllowPrivateAccess = "true"))
		class USoundCue* PickupSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ItemProperties, meta = (AllowPrivateAccess = "true"))
		 USoundCue* EquipSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ItemProperties, meta = (AllowPrivateAccess = "true"))
		int32 MaterialIndex = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ItemProperties, meta = (AllowPrivateAccess = "true"))
		UMaterialInstanceDynamic* DynamicMaterialInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ItemProperties, meta = (AllowPrivateAccess = "true"))
		UMaterialInstance* MaterialInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
		EItemType ItemType=EItemType::EIT_Weapon;


	bool bCanEnableCustomDepth=1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ItemProperties, meta = (AllowPrivateAccess = "true"))
		class UCurveVector* PulseCurve;

	FTimerHandle PulseTimer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ItemProperties, meta = (AllowPrivateAccess = "true"))
		float PulseCurveTime=5.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ItemProperties, meta = (AllowPrivateAccess = "true"))
		float GlowAmount=150.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ItemProperties, meta = (AllowPrivateAccess = "true"))
		float FresnelExponent=3.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ItemProperties, meta = (AllowPrivateAccess = "true"))
		float FresnelReflectFraction=4.f;

	

public:	
	

	FORCEINLINE UWidgetComponent* GetPickupWidget() const { return PickupWidget; }
	
	FORCEINLINE USphereComponent* GetAreaSphere() const { return AreaSphere; }

	FORCEINLINE UBoxComponent* GetCollisionBox() const { return CollisionBox; }

	FORCEINLINE EItemState GetItemState() const { return ItemState; }
	void SetItemState(EItemState State);

	FORCEINLINE bool GetIsTwinBlast() const { return bIsTwinBlast; }

	FORCEINLINE USkeletalMeshComponent* GetItemMesh() const { return ItemMesh; }
	FORCEINLINE USkeletalMeshComponent* GetItemMeshx2() const { return ItemMeshx2; }

	FORCEINLINE USoundCue* GetPickupSound() const { return PickupSound; }
	FORCEINLINE USoundCue* GetEquipSound() const { return EquipSound; }

	void StartItemCurve(AShooterCharacter* Char);
	FORCEINLINE int32 GetItemCount() const { return ItemCount; }





};
