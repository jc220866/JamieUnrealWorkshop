// Fill out your copyright notice in the Description page of Project Settings.

// The header file.
#include "DoomPlayerWeapon.h"

// So we can add and use the statis mesh functions.
#include "Components/StaticMeshComponent.h"

// So we can add and use the 'light' functions.
#include "Components/PointLightComponent.h"

// So we can spawn the actors and do other things related to the world.
#include "Engine/World.h"

// Sets default values
ADoomPlayerWeapon::ADoomPlayerWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create an empty scene component.
	USceneComponent* sceneComp = CreateDefaultSubobject<USceneComponent>("ROOT");

	// Make this empty component the root object.
	SetRootComponent(sceneComp);

	// Create the weapon mesh.
	weaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("WEAPON_MESH");

	// Attach the mesh to the root componetnt of the actor.
	weaponMesh->SetupAttachment(GetRootComponent());

	// Create the weapon light (muzzle flash).
	weaponLight = CreateDefaultSubobject<UPointLightComponent>("WEAPON_LIGHT");

	// Attach the light to the root component of the actor.
	weaponLight->SetupAttachment(GetRootComponent());

	// hide the component initially because we dont need the muzzle flash immediately
	weaponLight->SetHiddenInGame(true);
}

// Called when the game starts or when spawned
void ADoomPlayerWeapon::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADoomPlayerWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADoomPlayerWeapon::OnWeaponShoot()
{
}

bool ADoomPlayerWeapon::Shoot()
{
	if (GetWorld()->GetTimeSeconds() < nextFire)
		return false;

	if (currentAmmo <= 0)
		return false;

	currentAmmo--;
	nextFire = GetWorld()->GetTimeSeconds() < rateOfFire;

	OnWeaponShoot();
	BPEVENT_OnWeaponShoot();

	return true;
}
