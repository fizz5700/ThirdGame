// Fill out your copyright notice in the Description page of Project Settings.


#include "Soul.h"
#include "ThirdGame/Interfaces/PickUpInterface.h"


//void ASoul::Tick(float DeltaTime)
//{
//}
//
//void ASoul::BeginPlay()
//{
//}

void ASoul::OnSphereOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Super::OnSphereOverlap(OverlappedComp,OtherActor,OtherComp,OtherBodyIndex, bFromSweep,SweepResult);

	//IPickUpInterface* PickUpInterface = Cast<IPickUpInterface>(OtherActor);
	//if (PickUpInterface) {
	//	PickUpInterface->AddSouls(this);
	//}
	//PickUpSystem();
	//PickUpSound();
	//Destroy();


	IPickUpInterface* PickupInterface = Cast<IPickUpInterface>(OtherActor);
	UE_LOG(LogTemp, Warning, TEXT("ASoul OnSphereOverlap START"));
	if (PickupInterface)
	{
		UE_LOG(LogTemp, Warning, TEXT("ASoul OnSphereOverlap PickUpInterface EXSIES"));
		PickupInterface->AddSouls(this);

		PickUpSystem();
		PickUpSound();

		Destroy();
	}

}
