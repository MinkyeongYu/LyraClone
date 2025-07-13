// Copyright Epic Games, Inc. All Rights Reserved.

#include "LyraCloneGame.h"
#include "Modules/ModuleManager.h"
#include "LogChannels.h"

/* Custom Module */
class FLyraCloneGameModule : public FDefaultGameModuleImpl
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

void FLyraCloneGameModule::StartupModule()
{
	FDefaultGameModuleImpl::StartupModule();
	UE_LOG(LogLyra, Warning, TEXT("Startup Module!"));
}

void FLyraCloneGameModule::ShutdownModule()
{
	FDefaultGameModuleImpl::ShutdownModule();
}

/* PRIMARY_GAME_MODULE : Engine 내에서 딱 하나만 존재해야 함 */
IMPLEMENT_PRIMARY_GAME_MODULE( FLyraCloneGameModule, LyraCloneGame, "LyraCloneGame" );
