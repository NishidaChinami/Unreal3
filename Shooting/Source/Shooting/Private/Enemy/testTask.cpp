// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/testTask.h"
#include <AIController.h>
#include <NavigationPath.h>
#include <BehaviorTree/BlackboardComponent.h>
#include <BehaviorTree/Blackboard/BlackboardKeyType_Object.h>
#include <VisualLogger/VisualLogger.h>

UtestTask::UtestTask() :Super()
{
	NodeName = TEXT("CustomMoveTo");
	bNotifyTick = true;
	navSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

	// ブラックボードから渡されるターゲットのクラスをPawnに限定
	BlackboardKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UtestTask, BlackboardKey), APawn::StaticClass());
}

EBTNodeResult::Type UtestTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto pBlackboard = OwnerComp.GetBlackboardComponent();
	auto pKeyValue = pBlackboard->GetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID());
	pTarget = Cast<APawn>(pKeyValue);

	// Tickで移動処理するのでInProgressを返す
	return EBTNodeResult::InProgress;
	//return EBTNodeResult::Type();
}

void UtestTask::OnGameplayTaskActivated(UGameplayTask& Task)
{
}

void UtestTask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	//敵のAIと敵自体の取得
	auto pController = OwnerComp.GetAIOwner();
	auto pOwner = pController->GetPawn();

	// ターゲットに到達しているのかの判定
	auto distance = pOwner->GetActorLocation() - pTarget->GetActorLocation();
	if (distance.SquaredLength() > acceptableRadius * acceptableRadius)
	{
		auto movement = CalcMovement(pOwner);

		if (!movement.IsZero())
		{
			pOwner->AddMovementInput(movement, speed_delay);
		}
	}
	else
	{
		// タスクの正常終了を通知
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

	return;
}

FVector UtestTask::CalcMovement(const APawn* pOwner)
{
	// NavigationMeshを用いて移動経路を探索
	auto pPath = navSys->FindPathToActorSynchronously(GetWorld(), pOwner->GetActorLocation(), pTarget);
	if (!pPath) return FVector::Zero();

	auto& pathPoints = pPath->PathPoints;

	if (pathPoints.Num() >= 2)
	{
		// 自身の座標から初めの地点への方向を返す
		auto dir = pathPoints[1] - pathPoints[0];
		dir.Normalize();
		return dir;
	}
	else
	{
		return FVector::Zero();
	}
	return FVector();
}
