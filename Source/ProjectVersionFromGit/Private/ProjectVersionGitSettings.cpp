// Copyright 2025 Andrew Bindraw. All Rights Reserved.

#include "ProjectVersionGitSettings.h"

DEFINE_LOG_CATEGORY(LogProjectVersionGitSettings)

FPostInitPropertiesDelegate UProjectVersionGitSettings::OnPostInitPropertiesCompleted;

#if WITH_EDITOR
FPostEditChangePropertyDelegate UProjectVersionGitSettings::OnPostEditChangePropertyCompleted;
#endif

UProjectVersionGitSettings::UProjectVersionGitSettings(const FObjectInitializer& ObjectInitializer):
    Super(ObjectInitializer)
{
    /*
     * Check more info about git path:
     * Engine/Plugins/Developer/GitSourceControl/Source/GitSourceControl/Private/GitSourceControlUtils.cpp#L170
     * FString FindGitBinaryPath()
     * Open terminal
     * $ whereis git
     * $ which -a git
    */

#if PLATFORM_WINDOWS
    GitBinPath = "git.exe";
#else
    GitBinPath = "/usr/bin/git";
#endif
}

void UProjectVersionGitSettings::PostInitProperties()
{
    Super::PostInitProperties();

#if WITH_EDITOR
    static const FString ConfigIniName = TEXT("DefaultProjectVersionGitSettings.ini");
    static const FString ConfigIniPath = FConfigCacheIni::NormalizeConfigIniPath(FString::Printf(TEXT("%s%s"), *FPaths::SourceConfigDir(), *ConfigIniName));
    static const FString SectionName = TEXT("/Script/ProjectVersionFromGit.ProjectVersionGitSettings");

    if (!FPaths::FileExists(ConfigIniPath))
    {
        FConfigFile ConfigFile;
        GConfig->SetFile(ConfigIniPath, &ConfigFile);

        GConfig->SetString(
            *SectionName,
            TEXT("GitBinPath"),
            *GitBinPath,
            ConfigIniPath
        );

        GConfig->Flush(false, ConfigIniPath);

        UE_LOG(LogProjectVersionGitSettings, Log, TEXT("---> Created Config: %s, Path: %s"), *ConfigIniName, *ConfigIniPath);
    }
    else
    {
        GConfig->GetString(
            *SectionName,
            TEXT("GitBinPath"),
            GitBinPath,
            ConfigIniPath
        );
    }
#endif // WITH_EDITOR

    UE_LOG(LogProjectVersionGitSettings, Log, TEXT("---> PostInitProperties, GitBinPath: %s"), *GitBinPath);

    OnPostInitPropertiesCompleted.Broadcast();
}

#if WITH_EDITOR
void UProjectVersionGitSettings::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    UE_LOG(LogProjectVersionGitSettings, Log, TEXT("---> PostEditChangeProperty, GitBinPath: %s"), *GitBinPath);

    OnPostEditChangePropertyCompleted.Broadcast();
}
#endif // WITH_EDITOR
