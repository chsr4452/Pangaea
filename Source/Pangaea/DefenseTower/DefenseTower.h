// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DefenseTower.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS(Blueprintable)
class PANGAEA_API ADefenseTower : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADefenseTower();
	


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int HealthPointsCurrent;
	float ReloadCountingDown;
	
	void DestroyProcess();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Tower Params") int HealthPoints = 100;
	UPROPERTY(EditAnywhere, Category = "Tower Params") int ShellDefense = 2;
	UPROPERTY(EditAnywhere, Category = "Tower Params") float AttackRange = 15.0f;
	UPROPERTY(EditAnywhere, Category = "Tower Params") float ReloadInterval = 1.0f;

	//public functions
	UFUNCTION(BlueprintCallable, Category = "Pangaea|Defense Tower") int GetHealthPoints() const;
	UFUNCTION(BlueprintCallable, Category = "Pangaea|Defense Tower") bool IsDestroyed() const;
	UFUNCTION(BlueprintCallable, Category = "Pangaea|Defense Tower")bool CanFire() const;
	UFUNCTION(BlueprintCallable, Category = "Pangaea|Defense Tower")void Fire() const;
	UFUNCTION(BlueprintCallable, Category = "Pangaea|Defense Tower")void Hit(int Damage) const;

	FORCEINLINE USphereComponent * GetSphereComponent() const
	{
		return SphereComponent;
	}

	FORCEINLINE UStaticMeshComponent * GetMeshComponent() const
	{
		return MeshComponent;
	}
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tower Component", meta = (AllowPrivateAccess = true))
	TObjectPtr<USphereComponent> SphereComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tower Component", meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> MeshComponent;
};
