// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DoomPlayerWeapon.h"
#include "DoomLineTraceWeapon.generated.h"

/**
 * 
 */
UCLASS()
class UNREALWORKSHOP_API ADoomLineTraceWeapon : public ADoomPlayerWeapon
{
	GENERATED_BODY()
	
	
public: 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponSettings)
		float weaponRange = 10000;

protected: // Protected is Private but it is accessible to every class that inherits from this class!

	void OnWeaponShoot() override;
	
};
