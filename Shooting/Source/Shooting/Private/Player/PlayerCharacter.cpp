// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputActionValue.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// カメラ作成
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // カメラの位置
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// プレイヤー作成
	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PlayerMesh1P"));
	USkeletalMesh* SK_Mesh = LoadObject<USkeletalMesh>(nullptr, TEXT("/Game/FirstPersonArms/Character/Mesh/SK_Mannequin_Arms"));
	FirstPersonMesh->SetOnlyOwnerSee(true);
	FirstPersonMesh->SetupAttachment(FirstPersonCameraComponent);
	FirstPersonMesh->SetSkeletalMesh(SK_Mesh);
	FirstPersonMesh->bCastDynamicShadow = false;
	FirstPersonMesh->CastShadow = false;
	FirstPersonMesh->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	FirstPersonMesh->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	// 入力マッピングコンテキスト「IM_Controls」を読み込む
	DefaultMappingContext = LoadObject<UInputMappingContext>(nullptr, TEXT("/Game/Player/BluePrints/Input/IM_Controls"));

	// 
	MoveAction = LoadObject<UInputAction>(nullptr, TEXT("/Game/Player/BluePrints/Input/Action/IA_Move"));

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(GEngine != nullptr);

	// マッピングコンテキストを追加
	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller)) 
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) 
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	// デバッグメッセージを5秒間表示する。
	// Key "の値が-1であれば、メッセージの更新やリフレッシュは行われない。
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using PlayerCharacter."));
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerCharacter::ReceiveAnyDamage(float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser) {

	UKismetSystemLibrary::PrintString(this, "プレイヤーに当たりました", true, true, FColor::Cyan, 2.f, TEXT("None"));

}