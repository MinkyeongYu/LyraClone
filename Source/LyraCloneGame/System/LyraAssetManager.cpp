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

	// UE_LOG�� fatal�� ���� crash -> dummy�� ����
	return *NewObject<ULyraAssetManager>();
}

/* �ֿܼ� -LogAssetLoads �ְ� �����ϸ� ������ �α׸� ��� �Ǵ� ��� */
bool ULyraAssetManager::ShouldLogAssetLoads()
{
	// Cmd ���� LogAssetLoads�� �����ϴ��� �Ǵ� �� ��ȯ
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

		// 1. AssetManager�� ������, AssetManager�� StreamableManager�� ���� ���� �ε�
		// 2. FSoftObjectPath�� ���� �ٷ� ���� �ε�
		if (ULyraAssetManager::IsValid())
		{
			return ULyraAssetManager::GetStreamableManager().LoadSynchronous(AssetPath);
		}

		// StaticLoadObject ���� StaticFindObject�� ���� Ȯ�� �� �ε�, �ſ� ����
		return AssetPath.TryLoad();
	}
}