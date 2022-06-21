// Ultimate Apex Shooter.All Rights Reserved..


#include "Animation/STUAnimNotify.h"

void USTUAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) {
	OnNotified.Broadcast(MeshComp);
	Super::Notify(MeshComp, Animation, EventReference);


}