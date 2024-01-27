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

	// �u���b�N�{�[�h����n�����^�[�Q�b�g�̃N���X��Pawn�Ɍ���
	BlackboardKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UtestTask, BlackboardKey), APawn::StaticClass());
}

EBTNodeResult::Type UtestTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto pBlackboard = OwnerComp.GetBlackboardComponent();
	auto pKeyValue = pBlackboard->GetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID());
	pTarget = Cast<APawn>(pKeyValue);

	// Tick�ňړ���������̂�InProgress��Ԃ�
	return EBTNodeResult::InProgress;
	//return EBTNodeResult::Type();
}

void UtestTask::OnGameplayTaskActivated(UGameplayTask& Task)
{
}

void UtestTask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	//�G��AI�ƓG���̂̎擾
	auto pController = OwnerComp.GetAIOwner();
	auto pOwner = pController->GetPawn();

	// �^�[�Q�b�g�ɓ��B���Ă���̂��̔���
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
		// �^�X�N�̐���I����ʒm
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

	return;
}

FVector UtestTask::CalcMovement(const APawn* pOwner)
{
	// NavigationMesh��p���Ĉړ��o�H��T��
	auto pPath = navSys->FindPathToActorSynchronously(GetWorld(), pOwner->GetActorLocation(), pTarget);
	if (!pPath) return FVector::Zero();

	auto& pathPoints = pPath->PathPoints;

	if (pathPoints.Num() >= 2)
	{
		// ���g�̍��W���珉�߂̒n�_�ւ̕�����Ԃ�
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
