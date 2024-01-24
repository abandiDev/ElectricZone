// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "CP_MainGameState.generated.h"

/**
 * 
 */
UCLASS()
class ELECTRICZONE_API ACP_MainGameState : public AGameState
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
		void AssignPlayZone(AActor* zone);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
		float ShrinkDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
		int LevelDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
		int InitialShrinkDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
		int TotalShrinks;

protected:
	FTimerHandle TimerHandle_Scale;

	struct FActorScaleData
	{
		AActor* TargetActor;
		FVector InitialScale;
		FVector FinalScale;
		float Duration;
		float ElapsedTime;
	};

	FActorScaleData ZoneScaleData;

	void UpdateZoneScale();
	AActor* PlayZone;
	int CompletedShrinks;
	
};
