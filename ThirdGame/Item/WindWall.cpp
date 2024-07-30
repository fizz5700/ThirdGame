// Fill out your copyright notice in the Description page of Project Settings.


#include "ThirdGame/Item/WindWall.h"
#include "Kismet/KismetSystemLibrary.h" 

void AWindWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const double LocationX = GetActorLocation().X;
	if (LocationX > DesiredX) {
		const FVector DeltaLocation = FVector(DriftRate * DeltaTime,0.f, 0.f);
		AddActorLocalOffset(DeltaLocation);
	}
}

void AWindWall::BeginPlay()
{
	Super::BeginPlay();
	const FVector Start = GetActorLocation();
	const FVector End = Start + FVector(350.f, 0.f, 0.f);

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery1);
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetOwner());
	FHitResult HitResult;
	UKismetSystemLibrary::LineTraceSingleForObjects(
		this,
		Start,
		End,
		ObjectTypes,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::None,
		HitResult,
		true
	);
	DesiredX = HitResult.ImpactPoint.X + 50.f;
	GetWorldTimerManager().SetTimer(TimerHandle_LifeSpanExpired, this, &AActor::LifeSpanExpired, InLifeSpan);
}

void AWindWall::LifeSpanExpired()
{
	Destroy();
	GetWorldTimerManager().ClearTimer(TimerHandle_LifeSpanExpired);
}



void AWindWall::OnSphereOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	//IPickUpInterface* PickupInterface = Cast<IPickUpInterface>(OtherActor);
	UE_LOG(LogTemp, Warning, TEXT("AWindWall OnSphereOverlap START"));
	if (OtherActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Destroy"));
		//PickUpSystem();
		//PickUpSound();
		if (OtherActor->ActorHasTag(FName("FlyObject"))) {
			OtherActor->Destroy();
		}
		
	}

}