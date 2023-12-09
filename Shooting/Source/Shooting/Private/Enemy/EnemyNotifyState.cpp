// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyNotifyState.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Animation/AnimSequenceBase.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include"Enemy/EnemySample.h"


void UEnemyNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float _TotalDuration)
{
    Super::NotifyBegin(MeshComp, Animation, _TotalDuration);
    TObjectPtr<AEnemySample>enm = Cast<AEnemySample>(MeshComp->GetOwner());
    if(enm != nullptr)enm->StartAnim();
}

void UEnemyNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    Super::NotifyEnd(MeshComp, Animation);
    TObjectPtr<AEnemySample>enm = Cast<AEnemySample>(MeshComp->GetOwner());
    if (enm != nullptr) enm->EndAnim();
}

void UEnemyNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
    Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);

}

