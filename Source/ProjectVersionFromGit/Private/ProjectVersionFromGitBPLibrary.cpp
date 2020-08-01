// Copyright 2020 Andrew Bindraw. All Rights Reserved.

#include "ProjectVersionFromGitBPLibrary.h"
#include "ProjectVersionFromGit.h"

FText UProjectVersionFromGitBPLibrary::ProjectVersion 			= FText::GetEmpty();
FText UProjectVersionFromGitBPLibrary::ProjectVersionFormatAll 	= FText::GetEmpty();
FText UProjectVersionFromGitBPLibrary::BranchName 				= FText::GetEmpty();
FText UProjectVersionFromGitBPLibrary::CommitHash 				= FText::GetEmpty();
FText UProjectVersionFromGitBPLibrary::DateTimeBuild 			= FText::GetEmpty();

int32 UProjectVersionFromGitBPLibrary::Major = 0;
int32 UProjectVersionFromGitBPLibrary::Minor = 0;
int32 UProjectVersionFromGitBPLibrary::Patch = 0;

FString UProjectVersionFromGitBPLibrary::GitStdOutput = FString(TEXT(""));

DEFINE_LOG_CATEGORY(ProjectVersionFromGit)

UProjectVersionFromGitBPLibrary::UProjectVersionFromGitBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	GetProjectVersion();
}

FText UProjectVersionFromGitBPLibrary::GetProjectVersion()
{
	static const FString DefaultGameIni = FString::Printf(TEXT("%sDefaultGame.ini"), *FPaths::SourceConfigDir());

	if (GEngine->IsEditor())
	{
		FString OutStdOut;
		FString OutStdErr;
		int32 OutReturnCode;
		static const FString OptionalWorkingDirectory = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir());

		FString TagNameArg;
		FPlatformProcess::ExecProcess(TEXT("git"), TEXT("rev-list --tags --max-count=1"), &OutReturnCode, &OutStdOut, &OutStdErr, *OptionalWorkingDirectory);

		TagNameArg = FString(TEXT("describe --tags ")) + OutStdOut.TrimStartAndEnd();
		FPlatformProcess::ExecProcess(TEXT("git"), *TagNameArg, &OutReturnCode, &OutStdOut, &OutStdErr, *OptionalWorkingDirectory);

		if (OutStdOut.IsEmpty())
		{
			ProjectVersion = FText::FromString(TEXT("0.0.0"));
			Major = Minor = Patch = 0;
		}
		else
		{
			OutStdOut = OutStdOut.TrimStartAndEnd();
			TArray<FString> OutArrayParse;
			OutStdOut.ParseIntoArrayWS(OutArrayParse, TEXT("."));

			if (OutArrayParse.Num() == 3)
			{
				FDefaultValueHelper::ParseInt(OutArrayParse[0], Major);
				FDefaultValueHelper::ParseInt(OutArrayParse[1], Minor);
				FDefaultValueHelper::ParseInt(OutArrayParse[2], Patch);

				ProjectVersion = FText::FromString(OutStdOut);
			}
			else
			{
				ProjectVersion = FText::FromString(TEXT("0.0.0"));
				Major = Minor = Patch = 0;
			}
		}

		DateTimeBuild = FText::FromString(FDateTime::UtcNow().ToString() + TEXT("-UTC"));

		GetProjectVersionBranchName();
		GetProjectVersionCommitHash();

		ProjectVersionFormatAll = FText::Format(FText::FromString(TEXT("{0}-{1}-{2}-{3}")), ProjectVersion, BranchName, CommitHash, DateTimeBuild);

		if (!GitStdOutput.IsEmpty())
		{
			UE_LOG(ProjectVersionFromGit, Warning, TEXT("-------- git status --short: %s"), *GitStdOutput);
		}

		GConfig->SetText(
			TEXT("/Script/EngineSettings.GeneralProjectSettings"),
			TEXT("ProjectVersion"),
			ProjectVersion,
			DefaultGameIni
		);

		GConfig->SetInt(
			TEXT("/Script/EngineSettings.GeneralProjectSettings"),
			TEXT("Major"),
			Major,
			DefaultGameIni
		);

		GConfig->SetInt(
			TEXT("/Script/EngineSettings.GeneralProjectSettings"),
			TEXT("Minor"),
			Minor,
			DefaultGameIni
		);

		GConfig->SetInt(
			TEXT("/Script/EngineSettings.GeneralProjectSettings"),
			TEXT("Patch"),
			Patch,
			DefaultGameIni
		);

		GConfig->SetText(
			TEXT("/Script/EngineSettings.GeneralProjectSettings"),
			TEXT("BranchName"),
			BranchName,
			DefaultGameIni
		);

		GConfig->SetText(
			TEXT("/Script/EngineSettings.GeneralProjectSettings"),
			TEXT("CommitHash"),
			CommitHash,
			DefaultGameIni
		);

		GConfig->SetText(
			TEXT("/Script/EngineSettings.GeneralProjectSettings"),
			TEXT("DateTimeBuild"),
			DateTimeBuild,
			DefaultGameIni
		);
	}
	else
	{
		GConfig->GetText(
			TEXT("/Script/EngineSettings.GeneralProjectSettings"),
			TEXT("ProjectVersion"),
			ProjectVersion,
			GGameIni
		);

		GConfig->GetInt(
			TEXT("/Script/EngineSettings.GeneralProjectSettings"),
			TEXT("Major"),
			Major,
			GGameIni
		);

		GConfig->GetInt(
			TEXT("/Script/EngineSettings.GeneralProjectSettings"),
			TEXT("Minor"),
			Minor,
			GGameIni
		);

		GConfig->GetInt(
			TEXT("/Script/EngineSettings.GeneralProjectSettings"),
			TEXT("Patch"),
			Patch,
			GGameIni
		);

		GConfig->GetText(
			TEXT("/Script/EngineSettings.GeneralProjectSettings"),
			TEXT("BranchName"),
			BranchName,
			GGameIni
		);

		GConfig->GetText(
			TEXT("/Script/EngineSettings.GeneralProjectSettings"),
			TEXT("CommitHash"),
			CommitHash,
			GGameIni
		);

		GConfig->GetText(
			TEXT("/Script/EngineSettings.GeneralProjectSettings"),
			TEXT("DateTimeBuild"),
			DateTimeBuild,
			GGameIni
		);
	}

	UE_LOG(ProjectVersionFromGit, Log, TEXT("-------- ProjectVersion: %s"), *ProjectVersion.ToString());
	UE_LOG(ProjectVersionFromGit, Log, TEXT("-------- Major: %d"), Major);
	UE_LOG(ProjectVersionFromGit, Log, TEXT("-------- Minor: %d"), Minor);
	UE_LOG(ProjectVersionFromGit, Log, TEXT("-------- Patch: %d"), Patch);
	UE_LOG(ProjectVersionFromGit, Log, TEXT("-------- BranchName: %s"), *BranchName.ToString());
	UE_LOG(ProjectVersionFromGit, Log, TEXT("-------- CommitHash: %s"), *CommitHash.ToString());
	UE_LOG(ProjectVersionFromGit, Log, TEXT("-------- DateTimeBuild: %s"), *DateTimeBuild.ToString());
	UE_LOG(ProjectVersionFromGit, Log, TEXT("-------- ProjectVersionFormatAll: %s"), *ProjectVersionFormatAll.ToString());
	//UE_LOG(ProjectVersionFromGit, Log, TEXT("-------- GGameIni: %s"), *GGameIni);
	//UE_LOG(ProjectVersionFromGit, Log, TEXT("-------- DefaultGameIni: %s"), *DefaultGameIni);

	return ProjectVersion;
}

FText UProjectVersionFromGitBPLibrary::GetProjectVersionBranchName()
{
	if (GEngine->IsEditor())
	{
		FString OutStdOut;
		FString OutStdErr;
		int32 OutReturnCode;
		static const FString OptionalWorkingDirectory = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir());

		if (GEngine->IsEditor())
		{
			FPlatformProcess::ExecProcess(TEXT("git"), TEXT("symbolic-ref --short HEAD"), &OutReturnCode, &OutStdOut, &OutStdErr, *OptionalWorkingDirectory);
			if (OutStdOut.IsEmpty())
			{
				BranchName = FText::FromString(TEXT("unknown"));
			}
			else
			{
				BranchName = FText::FromString(OutStdOut.TrimStartAndEnd());
			}
		}
	}

	return BranchName;
}

FText UProjectVersionFromGitBPLibrary::GetProjectVersionCommitHash()
{
	if (GEngine->IsEditor())
	{
		FString OutStdOut;
		FString OutStdErr;
		int32 OutReturnCode;
		static const FString OptionalWorkingDirectory = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir());

		FPlatformProcess::ExecProcess(TEXT("git"), TEXT("status --short"), &OutReturnCode, &OutStdOut, &OutStdErr, *OptionalWorkingDirectory);
		GitStdOutput = OutStdOut;

		if (OutStdOut.IsEmpty())
		{
			FPlatformProcess::ExecProcess(TEXT("git"), TEXT("describe --always --abbrev=8"), &OutReturnCode, &OutStdOut, &OutStdErr, *OptionalWorkingDirectory);
			CommitHash = FText::FromString(OutStdOut.TrimStartAndEnd());
		}
		else
		{
			CommitHash = FText::FromString(TEXT("unknown"));
		}
	}

	return CommitHash;
}

int32 UProjectVersionFromGitBPLibrary::GetProjectVersionMajor()
{
	return Major;
}

int32 UProjectVersionFromGitBPLibrary::GetProjectVersionMinor()
{
	return Minor;
}

int32 UProjectVersionFromGitBPLibrary::GetProjectVersionPatch()
{
	return Patch;
}

FText UProjectVersionFromGitBPLibrary::GetProjectVersionDateTimeBuild()
{
	return DateTimeBuild;
}

FText UProjectVersionFromGitBPLibrary::GetProjectVersionFormatAll()
{
	return ProjectVersionFormatAll;
}

