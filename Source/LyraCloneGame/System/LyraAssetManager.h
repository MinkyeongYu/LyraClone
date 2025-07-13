// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "LyraAssetManager.generated.h"

/**	LyraAssetManager
*	: ���ӿ��� ����� PrimaryAsset�� ����/�񵿱�� �ε��ϰų� ��ε��ϰ�, �ε� ������ �α��ϴ� �� ����ϴ� �߾� ���� Ŭ����
*/
UCLASS()
class LYRACLONEGAME_API ULyraAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
public:
	ULyraAssetManager();

	static ULyraAssetManager& Get();

	/* FScopeLogTime ��� ���� �Ǵ� */
	static bool ShouldLogAssetLoads();

	/* ���� ������� ������ �ε��ϴ� �Լ� */
	UObject* SynchronousLoadAsset(const FSoftObjectPath& AssetPath);

	/* ���� �ε����� BP�� Object�ε� */
	template <typename AssetType>
	static AssetType* GetAsset(const TSoftClassPtr<AssetType>& AssetPointer, bool bKeepInMemory = true);

	template <typename AssetType>
	static TSubclassOf<AssetType> GetSubClass(const TSoftClassPtr<AssetType>& AssetPointer, bool bKeepInMemory = true);

public:
	// GC ���
	UPROPERTY()
	TSet<TObjectPtr<const UObject>> LoadedAssets;
	// Object ���� Locking
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