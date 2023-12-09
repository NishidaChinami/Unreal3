// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"


class USkeletalMeshComponent;
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

	UPROPERTY(VisibleAnywhere, Category = "AI")
	class UPawnSensingComponent* PawnSensingComp;

	UFUNCTION()
	void OnSeePlayer(APawn* Pawn);

public :
	//コリジョン用
	UPROPERTY(VisibleAnywhere, Category = Goal, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent>SphereCollition;
	class USphereComponent* GetSphereCollition()const { return SphereCollition; }

private:

	UPROPERTY(VisibleAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> SpringArm;


public:
//関数群
	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	void ReceiveAnyDamage(float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
	UFUNCTION(BlueprintCallable)
	void StartAnim();

	UFUNCTION(BlueprintCallable)
	void EndAnim();
//　変数群
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
