// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTING_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadWrite)
	float Speed = 0.0f;
	UPROPERTY(BlueprintReadWrite)
	bool IsFall;
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
};
