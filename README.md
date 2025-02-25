# ProjectVersionFromGit
This plugin set version for project from git tag format MAJOR.MINOR.PATCH also set branch name, commit hash and utc-datetime build.

**C++/Blueprints functions:**
- GetProjectVersion()
- GetProjectVersionMajor()
- GetProjectVersionMinor()
- GetProjectVersionPatch()
- GetProjectVersionBranchName()
- GetProjectVersionCommitHash()
- GetProjectVersionDateTimeBuild()
- GetProjectVersionFormatAll()

# Install into Project
You can install manually by extracting archive (ProjectVersionFromGit-X.X.X-...zip) from
[Releases](https://github.com/mrbindraw/ProjectVersionFromGit/releases) to your project plugins folder  
or build example project (ExamplePrj-UEX.X-ProjectVersionFromGit-X.X.X.zip).  

# Install into Unreal Engine  
You can install it from the marketplace [ProjectVersionFromGit](https://www.fab.com/listings/044c4f9a-eedc-487b-a973-c1c940470373)

Manual:   
1. Download and extracting archive (ProjectVersionFromGit-X.X.X-...zip) from [Releases](https://github.com/mrbindraw/ProjectVersionFromGit/releases) to any disk path, for example: `D:\Plugins`  
2. Than open any terminal (cmd, powershell) in `D:\Plugins` folder  
3. Launch `RunUAT.bat` in the terminal, for example:
```  
D:\EpicGames\UE_5.4\Engine\Build\BatchFiles\RunUAT.bat BuildPlugin -Plugin=D:\Plugins\ProjectVersionFromGit\ProjectVersionFromGit.uplugin -Package=D:\Plugins\UE_5.4\ProjectVersionFromGit -Rocket
```  
4. If you see the message `BUILD SUCCESSFUL` in the terminal after the build is complete,  
copy the `ProjectVersionFromGit` folder from `D:\Plugins\UE_5.4` to `D:\EpicGames\UE_5.4\Engine\Plugins\Marketplace`  
> [!IMPORTANT]
> **The engine path and folder names may differ on your system.**
