// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"


#include "Weapon.generated.h"

class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class PANGAEA_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) ACharacter* Holder = nullptr;
	UPROPERTY(EditAnywhere, Category = "Weapon|Params") float Strength = 10;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category = "Weapon|Box Collision")
	TObjectPtr<UBoxComponent> WeaponBox;

	UPROPERTY(EditAnywhere, Category = "Weapon|Mesh")
	TObjectPtr<UStaticMeshComponent> WeaponMesh;

	UFUNCTION() void OnWeaponBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
	bool bWithInAttackRange(float AttackRange, AActor* Target);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
