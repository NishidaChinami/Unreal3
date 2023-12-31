// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
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

	// ジャンプ時間の調整
	JumpMaxHoldTime = 0.15f;

	// 入力マッピングコンテキスト「IM_Controls」を読み込む
	DefaultMappingContext = LoadObject<UInputMappingContext>(nullptr, TEXT("/Game/Player/BluePrints/Input/IM_Controls"));

	// 入力アクション「IA_Move」を読み込む
	MoveAction = LoadObject<UInputAction>(nullptr, TEXT("/Game/Player/BluePrints/Input/Action/IA_Move"));

	// 入力アクション「IA_Jump」を読み込む
	JumpAction = LoadObject<UInputAction>(nullptr, TEXT("/Game/Player/BluePrints/Input/Action/IA_Jump"));

	// 入力アクション「IA_Look」を読み込む
	LookAction = LoadObject<UInputAction>(nullptr, TEXT("/Game/Player/BluePrints/Input/Action/IA_Look"));

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

	// Actionをバインドする
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		// PlayerCharacterとIA_MoveのTriggeredをBindする
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);

		// PlayerCharacterとIA_JumpのTriggeredをBindする
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APlayerCharacter::StartJump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &APlayerCharacter::StopJump);

		// PlayerCharacterとIA_LookのTriggeredをBindする
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);

	}
}

void APlayerCharacter::ReceiveAnyDamage(float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser) {

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("プレイヤーに当たりました"));
	// UKismetSystemLibrary::PrintString(this, "プレイヤーに当たりました", true, true, FColor::Cyan, 2.f, TEXT("None"));
}

// プレイヤー移動関数
void APlayerCharacter::Move(const FInputActionValue& Value) {

	// FVector2Dに変換
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// 移動処理 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

// ジャンプ関数
void APlayerCharacter::StartJump() 
{
	bPressedJump = true;

	//GetCapsuleComponent()->SetCollisionProfileName(FName("OverlapAllDynamic"));
}

void APlayerCharacter::StopJump() 
{
	//bPressedJump = false;
}

// 視点移動関数
void APlayerCharacter::Look(const FInputActionValue& Value) {

	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr) 
	{
		// カメラの角度を変更
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);

		//// Pawnが持っているControlの角度を取得する
		//FRotator ControlRotate = GetControlRotation();

		//UGameplayStatics::GetPlayerController(this, 0)->SetControlRotation(FRotator(ControlRotate.Pitch, ControlRotate.Yaw, 0.0f));
	}
}