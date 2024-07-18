// Fill out your copyright notice in the Description page of Project Settings.


#include "ThirdGame/HUD/SlashHUD.h"
#include "ThirdGame/HUD/SlashOverlay.h"

void ASlashHUD::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if (World) {
		APlayerController* Controller=World->GetFirstPlayerController();
		if (Controller && SlashOverlayClass) {
			SlashOverlay=CreateWidget<USlashOverlay>(Controller,SlashOverlayClass);
			SlashOverlay->AddToViewport();
		}
	}
	
}
