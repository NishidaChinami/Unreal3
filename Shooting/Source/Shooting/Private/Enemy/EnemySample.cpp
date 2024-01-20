// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemySample.h"
#include"Components/CapsuleComponent.h"
#include "Components/SphereComponent.h" 
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "Perception/PawnSensingComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/PrimitiveComponent.h"


#include "Player/PlayerCharacter.h"
#include "Enemy/AIEnemyController.h"

// Sets default values
AEnemySample::AEnemySample()
{
	PrimaryActorTick.bCanEverTick = true;
	USkeletalMesh *EM_Mesh =LoadObject<USkeletalMesh>(nullptr, TEXT("/Game/Horror_Pack_Vol_1/Zombie_mutant/Mesh/SK_Zombie_mutant")); 
	GetMesh()->SetSkeletalMesh(EM_Mesh);
	
	SphereCollition = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereCollition->SetupAttachment(GetMesh());
	

	// Radiusを設定する
	SphereCollition->SetupAttachment(GetMesh(), FName(TEXT("Character_LeftHand2")));
	SphereCollition->SetSphereRadius(72.0f);

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));

	// 視野
	PawnSensingComp->SetPeripheralVisionAngle(60.f);
	// 見える範囲
	PawnSensingComp->SightRadius = 2000;
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AEnemySample::OnSeePlayer);
}

// Called when the game starts or when spawned
void AEnemySample::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AEnemySample::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemySample::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void AEnemySample::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (const APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor)) {
		UE_LOG(LogTemp, Display, TEXT("Hit"));
		UGameplayStatics::ApplyDamage(OtherActor, EnemyDamage, nullptr,nullptr, UDamageType::StaticClass());
	}
}

void AEnemySample::ReceiveAnyDamage(float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser) {
	float damage = Health -Damage;
	Health = FMath::Clamp(damage, 0, 250);
	//HealthとMaxHealthを割るとパーセンテージが求められる

}

void AEnemySample::StartAnim() {
	if(SphereCollition != nullptr)SphereCollition->SetCollisionProfileName(FName("BlockAll"));
}

void AEnemySample::EndAnim() {
	if (SphereCollition != nullptr)SphereCollition->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
}

void AEnemySample::OnSeePlayer(APawn* Pawn)
{
	AAIEnemyController* AIController = Cast<AAIEnemyController>(GetController());
	// プレイヤー
	APlayerCharacter* player = Cast<APlayerCharacter>(Pawn);

	if (AIController && player)
	{
		// AIControllerにプレイヤー情報を設定
		AIController->SetPlayerKey(player);
	}

	// 視野に入ったら画面に"See"と表示
	UKismetSystemLibrary::PrintString(this, "See", true, true, FColor::Blue, 2.f);
}


//bool AEnemySample::CanAttackEnemyWithModeName(const AActor* const Enemy, FName ModeName, int32& OutModeIndex) const
//{
//	FAttackMode am = FAttackMode();
//	am.Name = ModeName;
//
//	return CanAttackEnemyWithMode(Enemy, am, OutModeIndex);
//}
