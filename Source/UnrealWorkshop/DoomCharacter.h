// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DoomCharacter.generated.h"

class UCameraComponent; // Declare use of the camera class
class UWeaponInventory; // Declare use of our weapon inventory class

UCLASS()
class UNREALWORKSHOP_API ADoomCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADoomCharacter();

	void UpdateShootingActions();

	// camera component reference
	UPROPERTY(Category = DoomCharacter, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* camera;

	// reference to weapon component
	UPROPERTY(Category = DoomCharacter, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UWeaponInventory* inventory;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override; // override means we override 'pawn''s beginplay function with this one, we override the 

	// input functions for movement
	void MoveForward(float scale);
	void MoveLeftRight(float scale);
	void MoveAim(float scale);

	void ShootPressAction();
	void ShootReleaseAction();
	void CycleWeaponAction();

	// BP EVENTS ////

	// Called when current weapon is fired
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Current Weapon Shoot"))
		void BPEvent_OnCurrentWeaponShoot();

	// Called when current weapon is switched
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Current Weapon Switched"))
		void BPEvent_OnCurrentWeaponSwitched();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	bool isShooting;
	
};
