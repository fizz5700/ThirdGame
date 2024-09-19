// Fill out your copyright notice in the Description page of Project Settings.


#include "ThirdGame/HUD/SlashOverlay.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void USlashOverlay::SetHealthProgressBar(float Percent)
{
	if (HealthProgressBar) {
		HealthProgressBar->SetPercent(Percent);
	}
	
}

void USlashOverlay::SetStaminaProgressBar(float Percent)
{
	if (StaminaProgressBar) {
		StaminaProgressBar->SetPercent(Percent);
	}
}

void USlashOverlay::SetCureTimes(int32 Num)
{
	if (CureText) {
		CureText->SetText(FText::FromString(FString::Printf(TEXT("%d"), Num)));
	}
}

void USlashOverlay::SetGoldText(int32 Gold)
{
	if (GoldText) {
		GoldText->SetText(FText::FromString(FString::Printf(TEXT("%d"),Gold)));
	}
}

void USlashOverlay::SetSoulsText(int32 Souls)
{
	if (SoulsText) {
		SoulsText->SetText(FText::FromString(FString::Printf(TEXT("%d"), Souls)));
	}
}
