// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"

void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds) {
	//superの呼び出し
	Super::NativeUpdateAnimation(DeltaSeconds);
    //ABPのオーナーCharacterを取得する
    ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwningActor());

    //OwnerCharacterにまつわる処理
    if (OwnerCharacter != nullptr)
    {
        //速度を取得する
        Speed = OwnerCharacter->GetVelocity().Size();

        //空中にいるかどうかを取得する
        IsFall = OwnerCharacter->GetCharacterMovement()->IsFalling();
    }
}