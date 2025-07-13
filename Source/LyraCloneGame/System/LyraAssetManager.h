// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "LyraAssetManager.generated.h"

/**	LyraAssetManager
*	: 게임에서 사용할 PrimaryAsset을 동기/비동기로 로드하거나 언로드하고, 로드 과정을 로깅하는 데 사용하는 중앙 관리 클래스
*/
UCLASS()
class LYRACLONEGAME_API ULyraAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
public:
	ULyraAssetManager();

	static ULyraAssetManager& Get();

	/* FScopeLogTime 사용 유무 판단 */
	static bool ShouldLogAssetLoads();

	/* 동기 방식으로 에셋을 로드하는 함수 */
	UObject* SynchronousLoadAsset(const FSoftObjectPath& AssetPath);

	/* 정적 로딩으로 BP와 Object로딩 */
	template <typename AssetType>
	static AssetType* GetAsset(const TSoftClassPtr<AssetType>& AssetPointer, bool bKeepInMemory = true);

	template <typename AssetType>
	static TSubclassOf<AssetType> GetSubClass(const TSoftClassPtr<AssetType>& AssetPointer, bool bKeepInMemory = true);

public:
	// GC 대상
	UPROPERTY()
	TSet<TObjectPtr<const UObject>> LoadedAssets;
	// Object 단위 Locking
	FCriticalSection SyncObject;
};

template<typename AssetType>
inline AssetType* ULyraAssetManager::GetAsset(const TSoftClassPtr<AssetType>& AssetPointer, bool bKeepInMemory)
{
	return nullptr;
}

template<typename AssetType>
inline TSubclassOf<AssetType> ULyraAssetManager::GetSubClass(const TSoftClassPtr<AssetType>& AssetPointer, bool bKeepInMemory)
{
	return TSubclassOf<AssetType>();
}