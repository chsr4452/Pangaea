// Fill out your copyright notice in the Description page of Project Settings.


#include "Pangaea/DefenseTower/DefenseTower.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Pangaea/Player/PlayerAvatar.h"
#include "Projectile/Projectile.h"

// Sets default values
ADefenseTower::ADefenseTower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(FName("Sphere"), false);
	SetRootComponent(SphereComponent);
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"), false);
	MeshComponent->SetupAttachment(GetRootComponent());

	static ConstructorHelpers::FObjectFinder<UBlueprint>blueprint_finder(TEXT("/Script/Engine.Blueprint'/Game/TopDown/Blueprints/DefenseTower/Projectile/BP_Projectile.BP_Projectile'"));
	FireballClass = static_cast<UClass*>(blueprint_finder.Object->GeneratedClass);

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ADefenseTower::OnBeginOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ADefenseTower::OnEndOverlap);
	
}

// Called when the game starts or when spawned
void ADefenseTower::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickInterval(0.5f);
	
	
}

void ADefenseTower::DestroyProcess()
{
}

// Called every frame
void ADefenseTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(Target != nullptr)
	{
		Fire();
	}
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


void ADefenseTower::Hit(int Damage) const
{
}

void ADefenseTower::Fire() const
{
	auto Fireball = Cast<AProjectile>(GetWorld()->SpawnActor(FireballClass));
	FVector StartLocation = GetActorLocation();
	StartLocation.Z += 100.f;
	FVector TargetLocation = Target->GetActorLocation();
	TargetLocation.Z = StartLocation.Z;
	FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(StartLocation, TargetLocation);
	Fireball->SetActorLocation(StartLocation);
	Fireball->SetActorRotation(Rotation);
	
}

void ADefenseTower::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("OnBeginOverlap Activated."))
	APlayerAvatar* Player = Cast<APlayerAvatar>(OtherActor);
	if(Player)
	{
		Target = Player;
	}
}

void ADefenseTower::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("OnEndOverlap Activated."))
	if(Target != nullptr && OtherActor == Target)
	{
		Target = nullptr;
	}
}

