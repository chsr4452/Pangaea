// Fill out your copyright notice in the Description page of Project Settings.


#include "Pangaea/Player/PlayerAvatar.h"

#include "PlayerAnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "DSP/AllPassFilter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
APlayerAvatar::APlayerAvatar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// BoxComponent = CreateDefaultSubobject<UBoxComponent>(FName("Box"), false);
	// SetRootComponent(BoxComponent);
	//
	// MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(FName("Mesh"), false);
	// MeshComponent->SetupAttachment(GetRootComponent());

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(FName("SpringArm"), false);
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->SetUsingAbsoluteRotation(true);
	SpringArmComponent->TargetArmLength = 1200.f;
	SpringArmComponent->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	SpringArmComponent->bDoCollisionTest = false;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(FName("Camera"), false);
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->bUsePawnControlRotation = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	auto const MainCharacterMovement  = GetCharacterMovement();
	MainCharacterMovement->bOrientRotationToMovement = true;
	MainCharacterMovement->RotationRate = FRotator(0.f, 640.f, 0.f);
	MainCharacterMovement->bConstrainToPlane = true;
	MainCharacterMovement->bSnapToPlaneAtStart = true;

	
}

// Called when the game starts or when spawned
void APlayerAvatar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerAvatar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UPlayerAnimInstance * AnimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());

	AnimInstance->Speed = GetCharacterMovement()->Velocity.Size2D();

	if(AttackCountingDown == AttackInterval)
	{
		AnimInstance->State = EPlayerState::Attack;
	}
	if(AttackCountingDown > 0.f)
	{
		AttackCountingDown -= DeltaTime;
	}
}

// Called to bind functionality to input
void APlayerAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

int APlayerAvatar::GetHealthPoints() const
{
	return HealthPointsCurrent;
}

bool APlayerAvatar::IsKilled() const
{
	return HealthPointsCurrent <= 0.f;
}

bool APlayerAvatar::CanAttack() const
{
	UPlayerAnimInstance* AnimInst = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	
	
	return (AttackCountingDown <= 0.f && AnimInst->State == EPlayerState::Locomotion);
}

void APlayerAvatar::Attack()
{
	AttackCountingDown = AttackInterval;
}

void APlayerAvatar::Hit(int Damage) const
{
}

void APlayerAvatar::DieProcess()
{
	Destroy();
}

