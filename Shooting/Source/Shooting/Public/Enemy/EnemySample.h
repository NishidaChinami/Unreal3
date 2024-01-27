// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"


class USkeletalMeshComponent;
class USpringArmComponent;
class USphereComponent;

#include "EnemySample.generated.h"

/**
 * �쐬�ҁ@���c
 * �쐬��11��18��,12��2��
 * ���e�@�G�̃��b�V���̕`��A�G���̂̃_���[�W����A�U���̔���
 */

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

	UPROPERTY(VisibleAnywhere, Category = "AI")
	class UPawnSensingComponent* PawnSensingComp;

	UFUNCTION()
	void OnSeePlayer(APawn* Pawn);

public :
	//�R���W�����p
	UPROPERTY(VisibleAnywhere, Category = Goal, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent>SphereCollition;
	class USphereComponent* GetSphereCollition()const { return SphereCollition; }

private:

	UPROPERTY(VisibleAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> SpringArm;


public:
//�֐��Q
	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	void ReceiveAnyDamage(float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
	UFUNCTION(BlueprintCallable)
	void StartAnim();

	UFUNCTION(BlueprintCallable)
	void EndAnim();

	//UFUNCTION(BlueprintPure, Category = Attack)
	//bool CanAttackEnemyWithMode(const AActor* const Enemy, const FAttackMode& AMode, int32& OutModeIndex) const;

	//// �U���\���ǂ����𔻒�
	//UFUNCTION(BlueprintPure, Category = Attack)
	//bool CanAttackEnemyWithModeName(const AActor* const Enemy, FName ModeName, int32& OutModeIndex) const;
	//UFUNCTION(BlueprintCallable, Category = Attack)
	//void AttackEnemyWithModeName(const AActor* const Enemy, FName ModeName);
	//
	////�U���A�j���[�V����
	//UFUNCTION()
	//void SetCurrentAttackMode(FName NewAttackMode);
	
	
	//�@�ϐ��Q
public:
	UPROPERTY(EditAnywhere)
	float Health = 100;
	UPROPERTY(EditAnywhere)
	float MaxHealth = 100;
private:
	UPROPERTY(EditAnywhere, Category = Enemy)
	float HealthPercentage = 1;
	UPROPERTY(EditAnywhere, Category = Enemy)
	float EnemyDamage = 15.f;

};

