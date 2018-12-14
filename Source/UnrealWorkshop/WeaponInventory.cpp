// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponInventory.h"

#include "Engine/World.h"

#include "DoomPlayerWeapon.h"

// Sets default values for this component's properties
UWeaponInventory::UWeaponInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  
	// You can turn these features off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

bool UWeaponInventory::FireCurrentWeapon()
{
	return currentWeapon->Shoot();
}

bool UWeaponInventory::SwitchWeapon()
{
	// hide the old weapon, so long as the weapon index is valid
	// (i.e. it started at -1, so no weapon needs to be hidden)
	if (weaponIndex >= 0)
		weapons[weaponIndex]->SetActorHiddenInGame(true);

	// increment the weapon index
	weaponIndex++;

	// clamp the index so it never exceeds the weapon count
	if (weaponIndex >= weapons.Num())
		weaponIndex = 0;

	// equip it
	currentWeapon = weapons[weaponIndex];

	// this weapon BP is null, return false
	if ( ! currentWeapon)
		return false;

	// apply an offset (for the switch weapon animation)
	currentWeapon->AddActorLocalOffset(FVector(-25, -0, -25));

	// show the new weapon
	currentWeapon->SetActorHiddenInGame(false);
	
	// swiched weapon successfully
	return true;
}

bool UWeaponInventory::CanSwitchWeapon()
{
	if (weapons.Num() <= 1)
		return false;

	return true;
}

ADoomPlayerWeapon * UWeaponInventory::GetCurrentWeapon()
{
	return currentWeapon;
}

// Called when the game starts
void UWeaponInventory::BeginPlay()
{
	Super::BeginPlay();

	InitWeapons();
}

// Called every frame
void UWeaponInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// if there is no current weapon / if it is null
	if (!currentWeapon)
		return; // leave this function

	// grab the weapon's location in the world
	FVector v = currentWeapon->GetActorLocation();

	//

	// smoothly move it back to the centre
	v = FMath::Lerp(v, GetOwner()->GetActorLocation(), 10 * DeltaTime);

	// set the weapons location to this lerp'd location
	currentWeapon->SetActorLocation( v );
}

void UWeaponInventory::InitWeapons()
{
	// iterate through the list of weapons
	for (int i = 0; i < startingWeapons.Num(); i++)
	{
		ADoomPlayerWeapon* weapon = GetWorld()->SpawnActor<ADoomPlayerWeapon>(
			startingWeapons[i], GetOwner()->GetActorLocation(), FRotator::ZeroRotator);

		// if for some reason this fails, call continue (jump back to the loop)
		if ( ! weapon)
			continue;

		// attach the weapon to the character's root component
		weapon->AttachToComponent(
			GetOwner()->GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);

		// hide the weapon
		weapon->SetActorHiddenInGame(true);

		// add this weapon to the list
		weapons.Add(weapon);
	}
	// if no weapons are created, leave
	if (weapons.Num() <= 0)
		return;

	// set weapon index to be -1 initially
	weaponIndex = -1;

	// so we can switch to the first weapon
	SwitchWeapon();
}

bool UWeaponInventory::CanShoot()
{
	return false;
}

