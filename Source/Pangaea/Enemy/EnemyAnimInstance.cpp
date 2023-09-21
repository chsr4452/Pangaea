// Fill out your copyright notice in the Description page of Project Settings.


#include "Pangaea/Enemy/EnemyAnimInstance.h"
#include "Pangaea/Enemy/EnemyCharacter.h"

void UEnemyAnimInstance::OnStateAnimationEnds()
{
	if(State == EEnemyState::Attack)
	{
		State = EEnemyState::Locomotion;
	}
	else
	{
		auto Enemy = Cast<AEnemyCharacter>(GetOwningActor());
		if(State == EEnemyState::Hit)
		{
			if(Enemy->GetHealthPoints() > 0.f)
			{
				State = EEnemyState::Locomotion;
			}
			else
			{
				State = EEnemyState::Die;
			}
		}
		else
		{
			Enemy->DieProcess();
		}
	}
}
