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
 * 作成者　西田
 * 作成日1月13日
 * 内容　敵のAI 敵の視野角
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
	// AIControllerのPawn所持
	virtual void OnPossess(class APawn* InPawn) override;

	// AIControllerのPawn所持解除
	virtual void OnUnPossess() override;

	virtual void BeginPlay() override;



	UPROPERTY(EditDefaultsOnly, Category = AI)
	class UBehaviorTree* BehaviorTree;

	FORCEINLINE UBehaviorTreeComponent* GetBehaviorComp() const { return BehaviorComp; }
	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }

	
};
