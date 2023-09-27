// Fill out your copyright notice in the Description page of Project Settings.


#include "Pangaea/DefenseTower/Projectile/Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

		
	SphereComponent = CreateDefaultSubobject<USphereComponent>(FName("Sphere"), false);
	SetRootComponent(SphereComponent);
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"), false);
	MeshComponent->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

