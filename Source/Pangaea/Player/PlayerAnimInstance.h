// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UENUM(BlueprintType) enum class EPlayerState : uint8
{
	Locomotion = 0,
	Attack,
	Hit,
	Die
};

UCLASS()
class PANGAEA_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float Speed = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool IsAttacking;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) EPlayerState State = EPlayerState::Locomotion;

	UFUNCTION(BlueprintCallable) void OnStateAnimationEnds();
};
