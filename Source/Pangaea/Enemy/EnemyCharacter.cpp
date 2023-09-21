// Fill out your copyright notice in the Description page of Project Settings.


#include "Pangaea/Enemy/EnemyCharacter.h"
#include "Perception/PawnSensingComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Pangaea/Enemy/EnemyController.h"
#include "Pangaea/Enemy/EnemyAnimInstance.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(FName("PawnSensor"));
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	HealthPointsCurrent = HealthPoints;
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto AnimInst = Cast<UEnemyAnimInstance>(GetMesh()->GetAnimInstance());
	AnimInst->Speed = GetCharacterMovement()->Velocity.Size2D();

	if(AttackCountingDown == AttackInterval)
	{
		AnimInst->State = EEnemyState::Attack;
	}
	
	if(AttackCountingDown > 0.f)
	{
		AttackCountingDown -= DeltaTime;
	}
	
}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

int AEnemyCharacter::GetHealthPoints()
{
	return HealthPointsCurrent;
}

bool AEnemyCharacter::IsKilled()
{
	return true;
}

bool AEnemyCharacter::CanAttack()
{
	return true;
}

void AEnemyCharacter::Chase(APawn* TargetPawn)
{
}

void AEnemyCharacter::Attack()
{
}

void AEnemyCharacter::Hit(int Damage)
{
}

void AEnemyCharacter::DieProcess()
{
	Destroy();
}

