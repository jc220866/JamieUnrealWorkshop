// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoomPlayerWeapon.generated.h"

// Forward declaration is saying "assume I am going to define this" (and it already is defined in Unreal).
class UStaticMeshComponent; // Declare use of static mesh (forward declaration).
class UPointLightComponent; // Declare use of lights (i.e 'muzzle flash').

UCLASS()
class UNREALWORKSHOP_API ADoomPlayerWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoomPlayerWeapon();

	UPROPERTY(Category = DoomCharacter, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true")) 
		UStaticMeshComponent* weaponMesh;

	UPROPERTY(Category = DoomCharacter, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true")) 
		UPointLightComponent* weaponLight;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// EditAnywhere = Editable within the blueprint settings.
	// BlueprintReadWrite = Allows the value to be changed within the BP event graph.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponSettings) float rateOfFire = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponSettings) int maxAmmo = 8;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponSettings) int currentAmmo = 8;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponSettings) bool isAutomatic = true;
	
protected:

	virtual void OnWeaponShoot();

private:

	float nextFire = -1.0;

public:

	// The shoot function.
	bool Shoot();

	// BP EVENTS //

	// Called when the weapon is fired
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Weapon Shoot"))
		void BPEVENT_OnWeaponShoot();
};
