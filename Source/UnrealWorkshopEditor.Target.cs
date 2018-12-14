// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class UnrealWorkshopEditorTarget : TargetRules
{
	public UnrealWorkshopEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		
		BuildEnvironment = TargetBuildEnvironment.Shared;
		bUseSharedPCHs = true;

		ExtraModuleNames.AddRange( new string[] { "UnrealWorkshop" } );
	}
}
