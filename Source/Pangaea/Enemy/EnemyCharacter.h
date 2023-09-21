// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class PANGAEA_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();
	
	UPROPERTY(EditAnywhere, Category = "Pangaea|Enemy Params")	int HealthPoints = 100;
	UPROPERTY(EditAnywhere, Category = "Pangaea|Enemy Params")	float Strength = 5.0f;
	UPROPERTY(EditAnywhere, Category = "Pangaea|Enemy Params")	float Armor = 1.f;
	UPROPERTY(EditAnywhere, Category = "Pangaea|Enemy Params")	float AttackRange = 200.f;
	UPROPERTY(EditAnywhere, Category = "Pangaea|Enemy Params")	float AttackInterval = 3.f;


	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	int HealthPointsCurrent;
	float AttackCountingDown;
	APawn* ChasedTarget = nullptr;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION(BlueprintCallable, Category = "Pangaea|Enemy Functions") int GetHealthPoints();
	UFUNCTION(BlueprintCallable, Category = "Pangaea|Enemy Functions") bool IsKilled();
	UFUNCTION(BlueprintCallable, Category = "Pangaea|Enemy Functions") bool CanAttack();
	UFUNCTION(BlueprintCallable, Category = "Pangaea|Enemy Functions") void Chase(APawn* TargetPawn);
	UFUNCTION(BlueprintCallable, Category = "Pangaea|Enemy Functions") void Attack();
	UFUNCTION(BlueprintCallable, Category = "Pangaea|Enemy Functions") void Hit(int Damage);
	UFUNCTION(BlueprintCallable, Category = "Pangaea|Enemy Functions") void DieProcess();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true));
	class UPawnSensingComponent* PawnSensingComponent;
};
