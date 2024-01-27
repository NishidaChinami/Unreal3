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


// ==================================================================
// �쐬�F�O ���l
// �쐬���F2023 / 11 / 18
// 
// 2023 / 12 / 9 �ړ��A�W�����v�ǉ�
// ==================================================================
// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// �J�����쐬
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // �J�����̈ʒu
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// �v���C���[�쐬
	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PlayerMesh1P"));
	USkeletalMesh* SK_Mesh = LoadObject<USkeletalMesh>(nullptr, TEXT("/Game/FirstPersonArms/Character/Mesh/SK_Mannequin_Arms"));
	FirstPersonMesh->SetOnlyOwnerSee(true);
	FirstPersonMesh->SetupAttachment(FirstPersonCameraComponent);
	FirstPersonMesh->SetSkeletalMesh(SK_Mesh);
	FirstPersonMesh->bCastDynamicShadow = false;
	FirstPersonMesh->CastShadow = false;
	FirstPersonMesh->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	FirstPersonMesh->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	// �W�����v���Ԃ̒���
	JumpMaxHoldTime = 0.15f;

	// ���̓}�b�s���O�R���e�L�X�g�uIM_Controls�v��ǂݍ���
	DefaultMappingContext = LoadObject<UInputMappingContext>(nullptr, TEXT("/Game/Player/BluePrints/Input/IM_Controls"));

	// ���̓A�N�V�����uIA_Move�v��ǂݍ���
	MoveAction = LoadObject<UInputAction>(nullptr, TEXT("/Game/Player/BluePrints/Input/Action/IA_Move"));

	// ���̓A�N�V�����uIA_Jump�v��ǂݍ���
	JumpAction = LoadObject<UInputAction>(nullptr, TEXT("/Game/Player/BluePrints/Input/Action/IA_Jump"));

	// ���̓A�N�V�����uIA_Look�v��ǂݍ���
	LookAction = LoadObject<UInputAction>(nullptr, TEXT("/Game/Player/BluePrints/Input/Action/IA_Look"));

	// ���̓A�N�V�����uIA_Fire�v��ǂݍ���
	FireAction = LoadObject<UInputAction>(nullptr, TEXT("/Game/Player/BluePrints/Input/Action/IA_Fire"));

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(GEngine != nullptr);

	// �}�b�s���O�R���e�L�X�g��ǉ�
	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller)) 
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) 
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	// �f�o�b�O���b�Z�[�W��5�b�ԕ\������B
	// Key "�̒l��-1�ł���΁A���b�Z�[�W�̍X�V�⃊�t���b�V���͍s���Ȃ��B
	// GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("We are using PlayerCharacter."));
	
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

	// Action���o�C���h����
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		// PlayerCharacter��IA_Move��Triggered��Bind����
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);

		// PlayerCharacter��IA_Jump��Triggered��Bind����
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APlayerCharacter::StartJump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &APlayerCharacter::StopJump);

		// PlayerCharacter��IA_Look��Triggered��Bind����
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);

		// PlayerCharacter��IA_Look��Triggered��Bind����
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &APlayerCharacter::Fire);

	}
}

void APlayerCharacter::ReceiveAnyDamage(float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser) {

	// �f�o�b�O
	// GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("�v���C���[�ɓ�����܂���"));
	
	// UKismetSystemLibrary::PrintString(this, "�v���C���[�ɓ�����܂���", true, true, FColor::Cyan, 2.f, TEXT("None"));
}

// �v���C���[�ړ��֐�
void APlayerCharacter::Move(const FInputActionValue& Value) {

	// FVector2D�ɕϊ�
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// �ړ����� 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

// �W�����v�֐�
void APlayerCharacter::StartJump() 
{
	bPressedJump = true;

	//GetCapsuleComponent()->SetCollisionProfileName(FName("OverlapAllDynamic"));
}

void APlayerCharacter::StopJump() 
{
	//bPressedJump = false;
}

// ���_�ړ��֐�
void APlayerCharacter::Look(const FInputActionValue& Value) {

	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr) 
	{
		// �J�����̊p�x��ύX
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);

		//// Pawn�������Ă���Control�̊p�x���擾����
		//FRotator ControlRotate = GetControlRotation();

		//UGameplayStatics::GetPlayerController(this, 0)->SetControlRotation(FRotator(ControlRotate.Pitch, ControlRotate.Yaw, 0.0f));
	}
}

// �e���ˊ֐�
void APlayerCharacter::Fire() 
{
	// Attemppt to fire a projectile
	if (ProjectileClass) {

		// GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Fire."));

		// Get the Camera transform
		FVector CameraLocation;
		FRotator CameraRotation;

		GetActorEyesViewPoint(CameraLocation, CameraRotation);

		// Set MuzzleOffset to spawn projectile slightly in front of the camera.
		MuzzleOffset.Set(100.0f, 0.0f, 0.0f);

		// Transform MuzzleOffset from camera space to world space.
		FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);

		// Skew the aim to be slightly upwards.
		// �_������������ɌX����B
		FRotator MuzzleRotation = CameraRotation;
		MuzzleRotation.Pitch += 10.0f;

		UWorld* World = GetWorld();
		if (World) {
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			// GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Fire. = spawn"));
			// Spawn the projectile at the muzzle.
			AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);

			if (Projectile) {
				// Set the projectile's initial trajectory.
				FVector LaunchDirection = MuzzleRotation.Vector();
				Projectile->FireInDirection(LaunchDirection);

			}
		}

	}
}