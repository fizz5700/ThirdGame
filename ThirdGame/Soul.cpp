// Fill out your copyright notice in the Description page of Project Settings.


#include "Soul.h"
#include "ThirdGame/Interfaces/PickUpInterface.h"

void ASoul::OnSphereOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereOverlap(OverlappedComp,OtherActor,OtherComp,OtherBodyIndex, bFromSweep,SweepResult);

	IPickUpInterface* PickUpInterface = Cast<IPickUpInterface>(OtherActor);
	if (PickUpInterface) {
		PickUpInterface->AddSoul(this);
	}
	Destroy();
}
