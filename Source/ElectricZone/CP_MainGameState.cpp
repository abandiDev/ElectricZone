// Fill out your copyright notice in the Description page of Project Settings.


#include "CP_MainGameState.h"
#include <Kismet/GameplayStatics.h>

void ACP_MainGameState::BeginPlay()
{
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName(FString::Printf(TEXT("zone"))), Actors);

	for (auto actor : Actors)
	{
		AssignPlayZone(actor);
		break;
	}
}

void ACP_MainGameState::AssignPlayZone(AActor* zone)
{
	PlayZone = zone;

	if (PlayZone)
	{
		FVector InitialScale = PlayZone->GetActorScale3D();
		FVector FinalScale = FVector(InitialScale.X - (InitialScale.X * 0.15f), InitialScale.Y - (InitialScale.Y * 0.15f), InitialScale.Z);

		ZoneScaleData.TargetActor = PlayZone;
		ZoneScaleData.InitialScale = InitialScale;
		ZoneScaleData.FinalScale = FinalScale;
		ZoneScaleData.Duration = ShrinkDuration;
		GetWorldTimerManager().SetTimer(TimerHandle_Scale, this, &ACP_MainGameState::UpdateZoneScale, 0.1f, true, InitialShrinkDelay);
	}
}

void ACP_MainGameState::UpdateZoneScale()
{
	if (ZoneScaleData.TargetActor)
	{
		ZoneScaleData.ElapsedTime += 0.1f;
		float Alpha = FMath::Clamp(ZoneScaleData.ElapsedTime / ZoneScaleData.Duration, 0.0f, 1.0f);

		FVector NewScale = FMath::Lerp(ZoneScaleData.InitialScale, ZoneScaleData.FinalScale, Alpha);

		ZoneScaleData.TargetActor->SetActorScale3D(NewScale);

		if (Alpha >= 1.0f)
		{
			CompletedShrinks += 1;

			GetWorldTimerManager().ClearTimer(TimerHandle_Scale);

			if (CompletedShrinks < TotalShrinks)
			{
				ZoneScaleData.InitialScale = ZoneScaleData.FinalScale;
				ZoneScaleData.FinalScale = FVector(ZoneScaleData.FinalScale.X - (ZoneScaleData.FinalScale.X * 0.15f), ZoneScaleData.FinalScale.Y - (ZoneScaleData.FinalScale.Y * 0.15f), ZoneScaleData.FinalScale.Z);
				ZoneScaleData.Duration = ShrinkDuration;
				ZoneScaleData.ElapsedTime = 0.0f;

				GetWorldTimerManager().SetTimer(TimerHandle_Scale, this, &ACP_MainGameState::UpdateZoneScale, 0.1f, true, InitialShrinkDelay);
			}
		}
	}
}
