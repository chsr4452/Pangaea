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
	PawnSensingComponent->SightRadius = 5000.f;
	PawnSensingComponent->SetPeripheralVisionAngle(45.f);
	
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	HealthPointsCurrent = HealthPoints;

	if(PawnSensingComponent)
	{
		PawnSensingComponent->OnSeePawn.AddDynamic(this, &AEnemyCharacter::PawnSeen);
	}
}

void AEnemyCharacter::PawnSeen(APawn* SeenPawn)
{
	if(SeenPawn->ActorHasTag(FName("PlayerCharacter")))
	{
		UE_LOG(LogTemp, Warning, TEXT("Pawn Seen!"));
		Chase(SeenPawn);
	}
}


// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UEnemyAnimInstance* AnimInst = Cast<UEnemyAnimInstance>(GetMesh()->GetAnimInstance());
	check(AnimInst);
	AnimInst->Speed = GetCharacterMovement()->Velocity.Size2D();
	
	if(AttackCountingDown == AttackInterval)
	{
		AnimInst->State = EEnemyState::Attack;
	}
	
	if(AttackCountingDown > 0.f)
	{
		AttackCountingDown -= DeltaTime;
	}

	if (ChasedTarget != nullptr && AnimInst->State == EEnemyState::Locomotion)
	{
		auto EnemyController = Cast<AEnemyController>(GetController());
		EnemyController->MakeAttackDecision(ChasedTarget);
	}
	
}

// Called to bind functionality to input
// void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
// {
// 	Super::SetupPlayerInputComponent(PlayerInputComponent);
// }

int AEnemyCharacter::GetHealthPoints()
{
	return HealthPointsCurrent;
}

bool AEnemyCharacter::IsKilled()
{
	return HealthPoints <= 0.f;
}

bool AEnemyCharacter::CanAttack()
{
	auto AnimInst = GetMesh()->GetAnimInstance();
	auto EnemyAnimInst = Cast<UEnemyAnimInstance>(AnimInst);
	
	return (AttackCountingDown <= 0.f && EnemyAnimInst->State == EEnemyState::Locomotion);
}

void AEnemyCharacter::Chase(APawn* TargetPawn)
{
	auto AnimInst = GetMesh()->GetAnimInstance();
	auto EnemyAnimInst = Cast<UEnemyAnimInstance>(AnimInst);
	if(TargetPawn != nullptr && EnemyAnimInst->State == EEnemyState::Locomotion)
	{
		auto EnemyController = Cast<AEnemyController>(GetController());
		EnemyController->MoveToActor(TargetPawn, 90.f);
	}
	ChasedTarget = TargetPawn;
}

void AEnemyCharacter::Attack()
{
	GetController()->StopMovement();
	AttackCountingDown = AttackInterval;
}

void AEnemyCharacter::Hit(int Damage)
{
	HealthPointsCurrent -= Damage;
	auto AnimInst = GetMesh()->GetAnimInstance();
	auto EnemyAnimInst = Cast<UEnemyAnimInstance>(AnimInst);
	EnemyAnimInst->State = EEnemyState::Hit;
	if(IsKilled())
	{
		DieProcess();
	}
}

void AEnemyCharacter::DieProcess()
{
	Destroy();
}

