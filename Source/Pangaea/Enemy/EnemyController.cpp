// Fill out your copyright notice in the Description page of Project Settings.


#include "Pangaea/Enemy/EnemyController.h"
#include "Pangaea/Enemy/EnemyCharacter.h"

void AEnemyController::MakeAttackDecision(APawn* TargetPawn)
{
	auto ControlledCharacter = Cast<AEnemyCharacter>(GetPawn());
	auto Dist = FVector::Dist2D(
	TargetPawn->GetActorLocation(),
	GetPawn()->GetTargetLocation());
	if(Dist <= ControlledCharacter->AttackRange&&ControlledCharacter->CanAttack())
	{
		ControlledCharacter->Attack();
	}
}
