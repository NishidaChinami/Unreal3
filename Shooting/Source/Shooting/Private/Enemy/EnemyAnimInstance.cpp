// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"

void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds) {
	//super�̌Ăяo��
	Super::NativeUpdateAnimation(DeltaSeconds);
    //ABP�̃I�[�i�[Character���擾����
    ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwningActor());

    //OwnerCharacter�ɂ܂�鏈��
    if (OwnerCharacter != nullptr)
    {
        //���x���擾����
        Speed = OwnerCharacter->GetVelocity().Size();

        //�󒆂ɂ��邩�ǂ������擾����
        IsFall = OwnerCharacter->GetCharacterMovement()->IsFalling();
    }
}