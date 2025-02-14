// Copyright 2025 Andrew Bindraw. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

#if WITH_EDITOR
#include "ISettingsModule.h"
#include "ProjectVersionGitSettings.h"
#endif

class FProjectVersionFromGitModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
