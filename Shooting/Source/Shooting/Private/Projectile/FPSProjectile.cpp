// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/FPSProjectile.h"
#include "Enemy/EnemySample.h"


// ==================================================================
// 作成：前 匠人
// 作成日：2024 / 1/ 20
// ==================================================================
// Sets default values
AFPSProjectile::AFPSProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent) 
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>( TEXT("ProjectileSceneComponent") );
	}

	// =============================================== エラー ===================================================================================

	if (!CollisionComponent) 
	{
		// Use a sphere as a simple collision representation
		CollisionComponent = CreateEditorOnlyDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));

		// Set the sphere's collision profile name to "Projectile".
		CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));

		// Event called when component hits something.
		CollisionComponent->OnComponentHit.AddDynamic(this, &AFPSProjectile::OnHit);
		// Set the sphere's collision radius.
		CollisionComponent->InitSphereRadius(15.0f);

		// Set the root component to be collision component.
		RootComponent = CollisionComponent;
	}

	if (!ProjectileMovementComponent) 
	{
		// Use this component to drive this projectile's movement.
		// このコンポーネントは、このプロジェクタイルの動きを駆動するために使用します。
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
		ProjectileMovementComponent->InitialSpeed = 3000.0f;
		ProjectileMovementComponent->MaxSpeed = 3000.0f;
		ProjectileMovementComponent->bRotationFollowsVelocity = true;
		ProjectileMovementComponent->bShouldBounce = true;
		ProjectileMovementComponent->Bounciness = 0.3f;
		ProjectileMovementComponent->ProjectileGravityScale = 0.0f;

	}
	if (!ProjectileMeshComponent) {
		ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
		UStaticMesh* Mesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/FPWeapon/Mesh/FirstPersonProjectileMesh"), NULL, LOAD_None, NULL);
		ProjectileMeshComponent->SetStaticMesh(Mesh);
		ProjectileMeshComponent->SetRelativeScale3D(FVector(0.09f, 0.09f, 0.09f));
		ProjectileMeshComponent->SetupAttachment(RootComponent);
	}
	// =============================================================================================================================================

	// Delete the projectile after 3 seconds.
	InitialLifeSpan = 1.0f;

}

// Called when the game starts or when spawned
void AFPSProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Function that initializes the projectile's velocity in the shoot direction.
void AFPSProjectile::FireInDirection(const FVector& ShootDirection) 
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}


// HitComponent = , OtherActor = 当たったアクタ, OtherComponent = ヒットしたキャラのコンポーネント, NomalImpulse = , Hit = .
void AFPSProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NomalImpulse, const FHitResult& Hit) {

	if (OtherActor != this && OtherComponent/*->IsSimulatingPhysics()*/) {

		AEnemySample* Enemy = Cast<AEnemySample>(OtherActor);

		// ダメージを与える
		if (Enemy) {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Enemy Hit!"));
			// Enemy->ReceiveAnyDamage();
		}

		// OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 100.0f, Hit.ImpactPoint);
	}

	// GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Destroy Projectile"));
	Destroy();
}

