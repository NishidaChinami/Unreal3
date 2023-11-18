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

	/** 球体衝突コンポーネント */
	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	USphereComponent* CollisionComp;

	/** 発射体移動コンポーネント */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

public:
	AShootingProjectile();

	/** 弾丸が何かに当たったときに呼ばれる */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** CollisionComp サブオブジェクトを返します。 **/
	USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** ProjectileMovement サブオブジェクトを返します。 **/
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
};

