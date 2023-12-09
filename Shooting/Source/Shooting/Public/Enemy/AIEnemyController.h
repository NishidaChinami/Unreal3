// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Player/PlayerCharacter.h"

#include "AIEnemyController.generated.h"

/**
 * Enemy�pAI�R���g���[���[
 */
UCLASS()
class SHOOTING_API AAIEnemyController : public AAIController
{
	GENERATED_BODY()
	
public:
	AAIEnemyController(const class FObjectInitializer& ObjectInitializer);
public:
	void SetPlayerKey(APawn* player);

	UFUNCTION()
	APlayerCharacter* GetPlayerKey();

	UPROPERTY()
	UBehaviorTreeComponent* BehaviorComp;

	UPROPERTY()
	UBlackboardComponent* BlackboardComp;

	UPROPERTY(EditDefaultsOnly, Category = AI)
	FName PlayerKeyName;

protected:
	// AIController��Pawn����
	virtual void OnPossess(class APawn* InPawn) override;

	// AIController��Pawn��������
	virtual void OnUnPossess() override;

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = AI)
	class UBehaviorTree* BehaviorTree;

	FORCEINLINE UBehaviorTreeComponent* GetBehaviorComp() const { return BehaviorComp; }
	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }
};
