// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerAvatar.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USkeletalMeshComponent;
class UBoxComponent;

UCLASS(Blueprintable)
class PANGAEA_API APlayerAvatar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerAvatar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int HealthPointsCurrent;
	float AttackCountingDown;

	void DieProcess();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = "Player Params") int HealthPoints = 500;
	UPROPERTY(EditAnywhere, Category = "Player Params") float Strength = 10.f;
	UPROPERTY(EditAnywhere, Category = "Player Params") float Armor = 3.f;
	UPROPERTY(EditAnywhere, Category = "Player Params") float AttackRange = 6.0f;
	UPROPERTY(EditAnywhere, Category = "Player Params") float AttackInterval = 1.2f;

	int GetHealthPoints() const;
	bool IsKilled() const;
	bool CanAttack() const;
	void Attack();
	void Hit(int Damage) const;


	// FORCEINLINE UBoxComponent * GetBoxComponent() const
	// {
	// 	return CapsuleComponent;
	// }
	//
	// FORCEINLINE USkeletalMeshComponent * GetMeshComponent() const
	// {
	// 	return MeshComponent;
	// }

	FORCEINLINE UCameraComponent* GetCameraComponent() const
	{
		return CameraComponent;
	}

	FORCEINLINE USpringArmComponent* GetSpringArmComponent() const
	{
		return SpringArmComponent;
	}
	
private:
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tower Component", meta = (AllowPrivateAccess = true))
	// TObjectPtr<UBoxComponent> BoxComponent;
	//
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tower Component", meta = (AllowPrivateAccess = true))
	// TObjectPtr<USkeletalMeshComponent> MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tower Component", meta = (AllowPrivateAccess = true))
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tower Component", meta = (AllowPrivateAccess = true))
	TObjectPtr<UCameraComponent> CameraComponent;
};
