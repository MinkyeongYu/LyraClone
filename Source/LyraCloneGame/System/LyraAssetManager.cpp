// Fill out your copyright notice in the Description page of Project Settings.


#include "LyraAssetManager.h"
#include "LyraCloneGame/LogChannels.h"

ULyraAssetManager::ULyraAssetManager()
{
}

ULyraAssetManager& ULyraAssetManager::Get()
{
	check(GEngine);

	if (ULyraAssetManager* Singleton = Cast<ULyraAssetManager>(GEngine->AssetManager))
	{
		return *Singleton;
	}

	UE_LOG(LogLyra, Fatal, TEXT("Invalid AssetManagerClassName in DefaultEngine.ini(project settings). It must be ULyraAssetManager"));

	// UE_LOG의 fatal로 인해 crash -> dummy로 리던
	return *NewObject<ULyraAssetManager>();
}

/* 콘솔에 -LogAssetLoads 넣고 실행하면 디버깅용 로그를 찍게 되는 방식 */
bool ULyraAssetManager::ShouldLogAssetLoads()
{
	// Cmd 에서 LogAssetLoads가 존재하는지 판단 후 반환
	const TCHAR* CommandLineContent = FCommandLine::Get();
	static bool bLogAssetLoads = FParse::Param(CommandLineContent, TEXT("LogAssetLoads"));
	return bLogAssetLoads;
}

UObject* ULyraAssetManager::SynchronousLoadAsset(const FSoftObjectPath& AssetPath)
{
	if (AssetPath.IsValid())
	{
		TUniquePtr<FScopeLogTime> LogTimePtr;
		if (ShouldLogAssetLoads())
		{
			LogTimePtr = MakeUnique<FScopeLogTime>(
				*FString::Printf(TEXT("Synchronous loaded assets [%s]"),*AssetPath.ToString()), nullptr
			);
		}

		// 1. AssetManager가 있으면, AssetManager의 StreamableManager를 통해 정적 로딩
		// 2. FSoftObjectPath를 통해 바로 정적 로딩
		if (ULyraAssetManager::IsValid())
		{
			return ULyraAssetManager::GetStreamableManager().LoadSynchronous(AssetPath);
		}

		// StaticLoadObject 전에 StaticFindObject를 통해 확인 후 로딩, 매우 느림
		return AssetPath.TryLoad();
	}
}