// Fill out your copyright notice in the Description page of Project Settings.

#include "DoomCharacter.h"

// Allows us to use the functions of PlayerInputComponent.
#include "Components/InputComponent.h"

// Allows us to use GEngine functions like AddOnScreenDebugMessage.
#include "Engine.h"

# include "Camera/CameraComponent.h"
# include "WeaponInventory.h"
# include "DoomPlayerWeapon.h"

// Sets default values - Constructor
ADoomCharacter::ADoomCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// create and initialize the camera compoenent
	camera = CreateDefaultSubobject<UCameraComponent>("CAMERA");

	// attach the camera to the root component of the actor
	camera->SetupAttachment(GetRootComponent());

	// create and iniialize the inventory component
	inventory = CreateDefaultSubobject<UWeaponInventory>("WEAPONS");

}

void ADoomCharacter::UpdateShootingActions()
{
	if ( ! isShooting)
		return;

	if (inventory->FireCurrentWeapon())
		BPEvent_OnCurrentWeaponShoot();
}

// Called when the game starts or when spawned
void ADoomCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADoomCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateShootingActions();
}

// Called to bind functionality to input
void ADoomCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//                              Name of input in Unreal, ourselves, specify the function to call
	PlayerInputComponent->BindAxis("MoveForwardBackward", this, &ADoomCharacter::MoveForward); // Creating a reference to the function (I think).
	PlayerInputComponent->BindAxis("MoveLeftRight", this, &ADoomCharacter::MoveLeftRight);

	PlayerInputComponent->BindAxis("MoveAim", this, &ADoomCharacter::MoveAim);

	PlayerInputComponent->BindAction("Shoot", EInputEvent::IE_Pressed, this, &ADoomCharacter::ShootPressAction);
	PlayerInputComponent->BindAction("Shoot", EInputEvent::IE_Released, this, &ADoomCharacter::ShootReleaseAction);

	PlayerInputComponent->BindAction("CycleCurrentWeapon", EInputEvent::IE_Pressed, this, &ADoomCharacter::CycleWeaponAction);
}

void ADoomCharacter::MoveForward(float scale)
{
	// GEngine->AddOnScreenDebugMessage(-1, 0.2f, FColor::Magenta, "MOVE FORWARD!");

	// move character (forward) based on scale
	AddMovementInput(GetActorForwardVector(), scale);
}

void ADoomCharacter::MoveLeftRight(float scale)
{
	// GEngine->AddOnScreenDebugMessage(-1, 0.2f, FColor::Purple, "MOVE SIDEWAYS!");

	// move character (sideways) based on scale
	AddMovementInput(GetActorRightVector(), scale);
}

void ADoomCharacter::MoveAim(float scale)
{
	// GEngine->AddOnScreenDebugMessage(-1, 0.2f, FColor::Blue, "LOOK AROUND!");

	// move camera (sideways) based on scale
	AddControllerYawInput(scale);
}

void ADoomCharacter::ShootPressAction()
{
	if ( ! inventory->GetCurrentWeapon()->isAutomatic &&
		inventory->FireCurrentWeapon())
		BPEvent_OnCurrentWeaponShoot();
	else isShooting = true;
}

void ADoomCharacter::ShootReleaseAction()
{
	isShooting = false;
}

void ADoomCharacter::CycleWeaponAction()
{
	if (inventory->CanSwitchWeapon() && inventory->SwitchWeapon())
		BPEvent_OnCurrentWeaponSwitched();
}

