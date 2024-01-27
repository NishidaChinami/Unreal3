// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "../Projectile/FPSProjectile.h"
#include "PlayerCharacter.generated.h"


class USkeletalMeshComponent;
class UCameraComponent;

// ==================================================================
// �쐬�F�O ���l
// �쐬���F2023 / 11 / 18
// 
// 2023 / 12 / 9 �ړ��A�W�����v�ǉ�
// ==================================================================
UCLASS()
class SHOOTING_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

private:

	// �J����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FirstPersonCameraComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* FirstPersonMesh;

	UPROPERTY(EditAnywhere, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	// �ړ�����
	UPROPERTY(EditAnywhere, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;

	// �W�����v����
	UPROPERTY(EditAnywhere, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> JumpAction;

	// ���_�ړ�����
	UPROPERTY(EditAnywhere, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookAction;

	// ���˓���
	UPROPERTY(EditAnywhere, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> FireAction;

	// �̗�
	float Life = 100.0f;

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// �ړ��֐�
	void Move(const FInputActionValue& Value);

	// �W�����v�֐�
	void StartJump();
	void StopJump();

	// ���_�ړ��֐�
	void Look(const FInputActionValue& Value);

protected:
	// Projectile class to spawn.
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AFPSProjectile> ProjectileClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 
	float getLife() { return Life; }

	void ReceiveAnyDamage(float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	// Function that handles firing projectiles.
	UFUNCTION()
	void Fire();

public:
	// Gun muzzle offset from the camera location.
	// �J�����ʒu����̏e���I�t�Z�b�g�B
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

};
