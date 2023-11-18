// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"


class UStaticMeshComponent;
class USpringArmComponent;
class USphereComponent;

#include "EnemySample.generated.h"
UCLASS()
class SHOOTING_API AEnemySample : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemySample();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	//Enemyのメッシュ（スキン）
	UPROPERTY(VisibleAnyWhere, Category = Character, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Zombie;
	//体の向きを取得

	UPROPERTY(VisibleAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> SpringArm;

	//コリジョン用
	UPROPERTY(VisibleAnywhere, Category = Goal, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent>Sphere;

//関数群
	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void ReceiveAnyDamage(float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

//　変数群
public:
	UPROPERTY(EditAnywhere)
	float Health = 100;
private:
	float HealthPercentage = 1;
	float EnemyDamege = 15;

};
