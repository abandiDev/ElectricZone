// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ELECTRICZONE_API ALobbyGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ALobbyGameMode();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	int32 brequiredNumberOfPlayers;
protected:
	virtual void PostLogin(APlayerController* NewPlayer) override;
};