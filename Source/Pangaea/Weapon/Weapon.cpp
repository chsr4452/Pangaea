// Fill out your copyright notice in the Description page of Project Settings.


#include "Pangaea/Weapon/Weapon.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Pangaea/Player/PlayerAvatar.h"
// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	WeaponBox = CreateDefaultSubobject<UBoxComponent>(FName("WeaponBox"));
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("WeaponMesh"));
	SetRootComponent(WeaponBox);
	WeaponMesh->SetupAttachment(GetRootComponent());
	
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &AWeapon::OnWeaponBeginOverlap);
}

void AWeapon::OnWeaponBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	UE_LOG(LogTemp, Log, TEXT("Weapon overlapped"));
	auto OtherCharacter = Cast<ACharacter>(OtherActor);
	if(OtherCharacter == nullptr)
	{
		return;
	}
	
	 if(Holder == nullptr)
	{
		auto const PlayerAvatar = Cast<APlayerAvatar>(OtherCharacter);
	 	if(PlayerAvatar != nullptr)
	 	{
	 		Holder = OtherCharacter;
	 		TArray<AActor*> AttachedActors;
	 		OtherActor->GetAttachedActors(AttachedActors, true);
	 		for(int i = 0; i < AttachedActors.Num(); ++i)
	 		{
	 			AttachedActors[i]->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	 			AttachedActors[i]->SetActorRotation(FQuat::Identity);
	 			AWeapon* Weapon = Cast<AWeapon>(AttachedActors[i]);
	 			Weapon->Holder = nullptr;
	 		}
	 		AttachToComponent(Holder->GetMesh(),FAttachmentTransformRules::SnapToTargetIncludingScale, FName("hand_rSocket"));
	 	}
	}
	// else if(bWithInAttackRange(0.f, OtherActor))
	// {
	// 	//
	// }
	
	
}



// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(Holder == nullptr)
	{
		FQuat rotQuat = FQuat(FRotator(0.f, 300.f * DeltaTime, 0.f));
	}
}


