// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShootingProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS(config=Game)
class AShootingProjectile : public AActor
{
	GENERATED_BODY()

	/** ���̏Փ˃R���|�[�l���g */
	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	USphereComponent* CollisionComp;

	/** ���ˑ̈ړ��R���|�[�l���g */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

public:
	AShootingProjectile();

	/** �e�ۂ������ɓ��������Ƃ��ɌĂ΂�� */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** CollisionComp �T�u�I�u�W�F�N�g��Ԃ��܂��B **/
	USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** ProjectileMovement �T�u�I�u�W�F�N�g��Ԃ��܂��B **/
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
};

