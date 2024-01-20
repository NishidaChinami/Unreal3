// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include <NavigationSystem.h>
#include "testTask.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTING_API UtestTask : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UtestTask();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnGameplayTaskActivated(UGameplayTask& Task);
	
protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	virtual FVector CalcMovement(const APawn* pOwner);

	APawn* pTarget;

	UNavigationSystemV1* navSys;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float acceptableRadius = 100.0f;
};

