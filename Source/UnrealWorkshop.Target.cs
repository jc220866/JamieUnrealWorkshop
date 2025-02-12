// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class UnrealWorkshopTarget : TargetRules
{
	public UnrealWorkshopTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		
		BuildEnvironment = TargetBuildEnvironment.Shared;

		ExtraModuleNames.AddRange( new string[] { "UnrealWorkshop" } );
	}
}
