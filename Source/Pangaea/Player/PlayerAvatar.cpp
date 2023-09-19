// Fill out your copyright notice in the Description page of Project Settings.


#include "Pangaea/Player/PlayerAvatar.h"

#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"


// Sets default values
APlayerAvatar::APlayerAvatar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(FName("Box"), false);
	SetRootComponent(BoxComponent);
	
	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(FName("Mesh"), false);
	MeshComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void APlayerAvatar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerAvatar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

int APlayerAvatar::GetHealthPoints() const
{
	return HealthPointsCurrent;
}

bool APlayerAvatar::IsKilled() const
{
	return HealthPointsCurrent <= 0.f;
}

bool APlayerAvatar::CanAttack() const
{
	return AttackCountingDown <= 0.f;
}

void APlayerAvatar::Attock() const
{
}

void APlayerAvatar::Hit(int Damage) const
{
}

