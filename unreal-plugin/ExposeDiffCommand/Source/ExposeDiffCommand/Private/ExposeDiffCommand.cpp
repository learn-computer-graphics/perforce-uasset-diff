// Copyright Epic Games, Inc. All Rights Reserved.

#include "ExposeDiffCommand.h"

#include "AssetToolsModule.h"
#include "DiffUtils.h"
#include "Modules/ModuleManager.h"
#include "Misc/PackagePath.h"
#include "Misc/Paths.h"
#include "HAL/IConsoleManager.h"
#include "UObject/ObjectRedirector.h"
#include "UObject/UObjectGlobals.h"

#define LOCTEXT_NAMESPACE "FExposeDiffCommandModule"

#if WITH_EDITOR

namespace ExposeDiffCommand
{
	// See SSourceControlReviewEntry::TryBindUAssetDiff()
	static UObject* GetAssetFromPath(const FString& Path)
	{
		const FPackagePath AssetPath = FPackagePath::FromLocalPath(Path);
		if (AssetPath.IsEmpty())
		{
			UE_LOG(LogExec, Warning, TEXT("Failed to find package for %s"), *Path);
			return nullptr;
		}

		UPackage* ReviewFilePkg = DiffUtils::LoadPackageForDiff(AssetPath, {});
		if (!ReviewFilePkg)
		{
			UE_LOG(LogExec, Warning, TEXT("Failed to load package for %s"), *Path);
			return nullptr;
		}

		const FString Filename = FPaths::GetBaseFilename(Path);
		UObject* Result = FindObject<UObject>(ReviewFilePkg, *Filename);
		if (!Result)
		{
			UE_LOG(LogExec, Warning, TEXT("Failed get UObject for %s"), *Filename);
			return nullptr;
		}

		if (Result->IsA<UObjectRedirector>())
		{
			Result = Cast<UObjectRedirector>(Result)->DestinationObject;
		}
		return Result;
	}

	static FAutoConsoleCommand DiffUAssetCommand(
		TEXT("diff.uasset"),
		TEXT("Open the diff view on two uassets to check their changes against one another.")
		TEXT("Use: \"diff.uasset 'AbsoluteAssetPath1' 'AbsoluteAssetPath2'\""),
		FConsoleCommandWithArgsDelegate::CreateLambda([](const TArray<FString>& Args)
			{
				if (Args.Num() != 2)
				{
					UE_LOG(LogExec, Warning, TEXT("Invalid arguments provided to diff command. Need 2, got %d"), Args.Num());
					return;
				}

				UObject* first = GetAssetFromPath(Args[0]);
				if (!first)
				{
					UE_LOG(LogExec, Warning, TEXT("Failed to open %s"), *Args[0]);
					return;
				}

				UObject* second = GetAssetFromPath(Args[1]);
				if (!second)
				{
					UE_LOG(LogExec, Warning, TEXT("Failed to open %s"), *Args[1]);
					return;
				}

				// Load the asset registry module
				FAssetToolsModule& AssetToolsModule = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools");
				AssetToolsModule.Get().DiffAssets(first, second, FRevisionInfo(), FRevisionInfo());
			}),
		ECVF_Cheat);
}

#endif // WITH_EDITOR

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FExposeDiffCommandModule, ExposeDiffCommand)