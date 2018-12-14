// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponInventory.generated.h"

class ADoomPlayerWeapon; // declaring use of our DoomWeapon class for line 24

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALWORKSHOP_API UWeaponInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponInventory();

	bool FireCurrentWeapon();
	bool SwitchWeapon();
	bool CanSwitchWeapon();

	ADoomPlayerWeapon* GetCurrentWeapon();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// our list of weapon *blueprints*
	UPROPERTY(Category = DoomWeapons, EditAnywhere)
		TArray <TSubclassOf <ADoomPlayerWeapon> > startingWeapons;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	TArray<ADoomPlayerWeapon*> weapons;
	void InitWeapons();
	int weaponIndex = 0;
	ADoomPlayerWeapon* currentWeapon;

	bool CanShoot();
	
};
