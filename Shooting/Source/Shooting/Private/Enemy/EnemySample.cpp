// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemySample.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AEnemySample::AEnemySample()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Zombie = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = Zombie;
	//Ç±Ç±Ç…ÉÅÉbÉVÉÖÇåàíË
	UStaticMesh* Mesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/RollingBall/Enviroment/Meshes/S_Goal"));
	Zombie->SetStaticMesh(Mesh);
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

void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

}

void ReceiveAnyDamage(float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser) {

}


