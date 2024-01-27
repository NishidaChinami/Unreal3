// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "EnemyNotifyState.generated.h"

/**
 * 作成者　西田
 * 作成日12月9日
 * 内容　敵の攻撃のAnimationNotify
 */
UCLASS(editinlinenew, Blueprintable,const,hidecategories = Object, collapsecategories, meta = (ShowWorldContextPin, DisplayName = "EnemyNotify"))
class SHOOTING_API UEnemyNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)override;
	

	
};
