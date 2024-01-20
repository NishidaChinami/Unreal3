// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/AIEnemyController.h"
#include "UObject/ConstructorHelpers.h"
#include <BehaviorTree/BlackboardComponent.h>
#include <Kismet/GameplayStatics.h>

AAIEnemyController::AAIEnemyController(const class FObjectInitializer& ObjectInitializer) {

	BehaviorComp = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
	BlackboardComp = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));

	// 作成したビヘイビアツリーを設定
	ConstructorHelpers::FObjectFinder<UBehaviorTree> BTFinder(TEXT("/Game/EnemyBP/Mutant/BT_Mutant"));

	BehaviorTree = BTFinder.Object;

	PlayerKeyName = "Player";
}

void AAIEnemyController::BeginPlay()
{
	Super::BeginPlay();
	// BlackboardにプレイヤーをTaragetActorとして登録
	auto pBlackBoard = GetBlackboardComponent();
	if (pBlackBoard)
	{
		pBlackBoard->SetValueAsObject(TEXT("TargetActor"), UGameplayStatics::GetPlayerPawn(this, 0));
	}
}
void AAIEnemyController::OnPossess(APawn* InPawn) {
	Super::OnPossess(InPawn);

	// AIControllerがPawn所持した際にBBとBTを使用
	BlackboardComp->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	BehaviorComp->StartTree(*BehaviorTree);
}

void AAIEnemyController::OnUnPossess()
{
	Super::OnUnPossess();
	BehaviorComp->StopTree();
}

void AAIEnemyController::SetPlayerKey(APawn* player)
{
	ensure(BlackboardComp);

	// ブラックボードで作成したPlayerというキーにプレイヤー情報を入れる
	BlackboardComp->SetValueAsObject(PlayerKeyName, player);
}

APlayerCharacter* AAIEnemyController::GetPlayerKey()
{
	ensure(BlackboardComp);

	return Cast<APlayerCharacter>(BlackboardComp->GetValueAsObject(PlayerKeyName));
}

