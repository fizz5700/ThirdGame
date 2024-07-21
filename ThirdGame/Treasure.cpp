// Fill out your copyright notice in the Description page of Project Settings.


#include "Treasure.h"
#include "ThirdGame/Interfaces/PickUpInterface.h"
void ATreasure::OnSphereOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IPickUpInterface* PickUpInterface = Cast<IPickUpInterface>(OtherActor);
	if (PickUpInterface) {
		PickUpInterface->AddGold(this);
		PickUpSound();
		Destroy();
	}

}
