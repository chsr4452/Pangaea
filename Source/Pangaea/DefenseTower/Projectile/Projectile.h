// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS(Blueprintable)
class PANGAEA_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float LifeCountingDown;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	float Speed = 100.0f;
	float Lifespan = 5.0f;
	float Damage = 10.f;

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
