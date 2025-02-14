// Copyright 2025 Andrew Bindraw. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Misc/ConfigCacheIni.h"
#include "ProjectVersionGitSettings.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogProjectVersionGitSettings, Log, All);

UCLASS(Config = ProjectVersionGitSettings, DefaultConfig)
class PROJECTVERSIONFROMGIT_API UProjectVersionGitSettings : public UObject
{
	GENERATED_BODY()
	
public:

    virtual void PostInitProperties() override;
    
	UPROPERTY(Config, EditAnywhere, Category = "Settings", DisplayName = "Path to git binary file")
	FString GitBinPath;
};
