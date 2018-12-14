// Fill out your copyright notice in the Description page of Project Settings.

#include "DoomLineTraceWeapon.h"
#include "Engine/World.h"
#include "Engine.h"

void ADoomLineTraceWeapon::OnWeaponShoot()
{
	// The hit result get populated by the line trace
	FHitResult Hit;
	FCollisionQueryParams params = FCollisionQueryParams(FName(), true);

	// linetrace start point
	FVector Start = GetActorLocation();

	// linetrace end point
	FVector End = GetActorLocation() + (GetActorForwardVector() * weaponRange);

	// do the line trace and if we hit something, display the name of the object
	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_Visibility, params))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, Hit.GetActor()->GetName());
	}
}
