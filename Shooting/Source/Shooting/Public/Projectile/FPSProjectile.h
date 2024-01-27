// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "FPSProjectile.generated.h"

// ==================================================================
// 作成：前 匠人
// 作成日：2024 / 1/ 20
// ==================================================================
UCLASS()
class SHOOTING_API AFPSProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSProjectile();

	// Function that initializes the projectile's velocity in the shoot direction.
	// 射出方向の速度を初期化する関数。
	void FireInDirection(const FVector& ShootDirection);

	// Function that is called when the projectile hits something.
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NomalImpulse, const FHitResult& Hit);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	TObjectPtr<USphereComponent> CollisionComponent;

	// Projectile movement component.
	UPROPERTY(VisibleAnywhere, Category = Movement)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

	// Projectile mesh
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	TObjectPtr<UStaticMeshComponent> ProjectileMeshComponent;

	// Projectile material
	/*UPROPERTY(VisibleDefaultsOnly, Category = Movement)
	TObjectPtr<UMaterialInstanceDynamic> ProjectileMaterialInstance;*/

private:

};
