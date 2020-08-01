// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Misc/DateTime.h"
#include "Misc/Paths.h"
#include "GenericPlatform/GenericPlatformProcess.h"
#include "Misc/DefaultValueHelper.h"
#include "Misc/ConfigCacheIni.h"

#include "Kismet/BlueprintFunctionLibrary.h"
#include "ProjectVersionFromGitBPLibrary.generated.h"

/* 
*	Function library class.
*	Each function in it is expected to be static and represents blueprint node that can be called in any blueprint.
*
*	When declaring function you can define metadata for the node. Key function specifiers will be BlueprintPure and BlueprintCallable.
*	BlueprintPure - means the function does not affect the owning object in any way and thus creates a node without Exec pins.
*	BlueprintCallable - makes a function which can be executed in Blueprints - Thus it has Exec pins.
*	DisplayName - full name of the node, shown when you mouse over the node and in the blueprint drop down menu.
*				Its lets you name the node using characters not allowed in C++ function names.
*	CompactNodeTitle - the word(s) that appear on the node.
*	Keywords -	the list of keywords that helps you to find node when you search for it using Blueprint drop-down menu. 
*				Good example is "Print String" node which you can find also by using keyword "log".
*	Category -	the category your node will be under in the Blueprint drop-down menu.
*
*	For more info on custom blueprint nodes visit documentation:
*	https://wiki.unrealengine.com/Custom_Blueprint_Node_Creation
*/
UCLASS()
class UProjectVersionFromGitBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintPure, Category = "ProjectVersionFromGit")
	static FText GetProjectVersion();

	UFUNCTION(BlueprintPure, Category = "ProjectVersionFromGit")
	static int32 GetProjectVersionMajor();

	UFUNCTION(BlueprintPure, Category = "ProjectVersionFromGit")
	static int32 GetProjectVersionMinor();

	UFUNCTION(BlueprintPure, Category = "ProjectVersionFromGit")
	static int32 GetProjectVersionPatch();

	UFUNCTION(BlueprintPure, Category = "ProjectVersionFromGit")
	static FText GetProjectVersionBranchName();

	UFUNCTION(BlueprintPure, Category = "ProjectVersionFromGit")
	static FText GetProjectVersionCommitHash();

	UFUNCTION(BlueprintPure, Category = "ProjectVersionFromGit")
	static FText GetProjectVersionDateTimeBuild();

	UFUNCTION(BlueprintPure, Category = "ProjectVersionFromGit")
	static FText GetProjectVersionFormatAll();

private:
	static FText ProjectVersion;
	static FText ProjectVersionFormatAll;
	static FText CommitHash;
	static FText BranchName;
	static FText DateTimeBuild;
	static int32 Major;
	static int32 Minor;
	static int32 Patch;

	static FString GitStdOutput;
};
