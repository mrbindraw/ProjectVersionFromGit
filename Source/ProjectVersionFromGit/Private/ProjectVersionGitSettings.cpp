// Copyright 2024 Andrew Bindraw. All Rights Reserved.

#include "ProjectVersionGitSettings.h"

DEFINE_LOG_CATEGORY(LogProjectVersionGitSettings)

void UProjectVersionGitSettings::PostInitProperties()
{
    Super::PostInitProperties();

#if WITH_EDITOR
    static const FString ConfigIniName = TEXT("DefaultProjectVersionGitSettings.ini");
    static const FString ConfigIniPath = FConfigCacheIni::NormalizeConfigIniPath(FString::Printf(TEXT("%s%s"), *FPaths::SourceConfigDir(), *ConfigIniName));
    
    if(!FPaths::FileExists(ConfigIniPath))
    {
        static const FString SectionName = TEXT("/Script/ProjectVersionFromGit.ProjectVersionGitSettings");
        
        FConfigFile ConfigFile;
        GConfig->SetFile(ConfigIniPath, &ConfigFile);
        
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
        
        GConfig->SetString(
            *SectionName,
            TEXT("GitBinPath"),
            *GitBinPath,
            ConfigIniPath
        );
        
        GConfig->Flush(false, ConfigIniPath);

        UE_LOG(LogProjectVersionGitSettings, Log, TEXT("---> Created Config: %s, Path: %s"), *ConfigIniName, *ConfigIniPath);
        UE_LOG(LogProjectVersionGitSettings, Log, TEXT("---> Set default value for GitBinPath: %s"), *GitBinPath);
    }
#endif //WITH_EDITOR
    
}
