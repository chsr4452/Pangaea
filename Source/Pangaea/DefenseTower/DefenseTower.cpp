// Fill out your copyright notice in the Description page of Project Settings.


#include "Pangaea/DefenseTower/DefenseTower.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ADefenseTower::ADefenseTower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(FName("Sphere"), false);
	SetRootComponent(SphereComponent);
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"), false);
	MeshComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ADefenseTower::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADefenseTower::DestroyProcess()
{
}

// Called every frame
void ADefenseTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int ADefenseTower::GetHealthPoints() const
{
	return HealthPointsCurrent;
}

bool ADefenseTower::IsDestroyed() const
{
	return HealthPointsCurrent <= 0.f;
}

bool ADefenseTower::CanFire() const
{
	return ReloadCountingDown <= 0.f;
}

void ADefenseTower::Fire() const
{
}

void ADefenseTower::Hit(int Damage) const
{
}

