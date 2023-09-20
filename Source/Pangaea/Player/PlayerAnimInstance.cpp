// Fill out your copyright notice in the Description page of Project Settings.


#include "Pangaea/Player/PlayerAnimInstance.h"
#include "PlayerAvatar.h"

void UPlayerAnimInstance::OnStateAnimationEnds()
{
	if(State == EPlayerState::Attack)
	{
		State = EPlayerState::Locomotion;
	}
	else
	{
		auto const OwnerActor = this->GetOwningActor();
		auto const PlayerAvatar = Cast<APlayerAvatar>(OwnerActor);

		if(PlayerAvatar == nullptr)
		{
			return;
		}
		if(State == EPlayerState::Hit)
		{
			if(PlayerAvatar->GetHealthPoints() > 0.f)
			{
				State = EPlayerState::Locomotion;
			}
			else
			{
				State = EPlayerState::Die;
			}
		}
		else if(State == EPlayerState::Die)
		{
			PlayerAvatar->Destroy();
		}
	}
}
