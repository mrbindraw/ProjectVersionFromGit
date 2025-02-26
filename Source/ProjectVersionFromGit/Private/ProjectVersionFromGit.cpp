// Copyright 2025 Andrew Bindraw. All Rights Reserved.

#include "ProjectVersionFromGit.h"

#define LOCTEXT_NAMESPACE "FProjectVersionFromGitModule"

void FProjectVersionFromGitModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
    
#if WITH_EDITOR
    ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");

    if (SettingsModule != nullptr)
    {
        SettingsModule->RegisterSettings("Project", "Plugins", "ProjectVersionGit",
            LOCTEXT("ProjectVersionGitSettingsName", "Project Version Git"),
            LOCTEXT("ProjectVersionGitSettingsDescription", "Configure the ProjectVersionFromGit plugin"),
            GetMutableDefault<UProjectVersionGitSettings>()
        );
    }
#endif //WITH_EDITOR
}

void FProjectVersionFromGitModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
    
#if WITH_EDITOR
    ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");
    if (SettingsModule != nullptr)
    {
        SettingsModule->UnregisterSettings("Project", "Plugins", "ProjectVersionGit");
    }
#endif //WITH_EDITOR
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FProjectVersionFromGitModule, ProjectVersionFromGit)
