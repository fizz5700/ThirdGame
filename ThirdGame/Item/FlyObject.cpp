// Fill out your copyright notice in the Description page of Project Settings.


#include "ThirdGame/Item/FlyObject.h"
#include "ThirdGame/Interfaces/HitInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h" 


void AFlyObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const double LocationX = GetActorLocation().X;
	if (LocationX > DesiredX) {
		const FVector DeltaLocation = FVector(DriftRate * DeltaTime, 0.f, 0.f);
		AddActorLocalOffset(DeltaLocation);
	}
}

void AFlyObject::BeginPlay()
{
	Super::BeginPlay();
	Tags.Add(FName("FlyObject"));

	const FVector Start = GetActorLocation();
	const FVector End = Start + FVector(0.f, 0.f, 0.f);

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

void AFlyObject::LifeSpanExpired()
{
	Destroy();
	GetWorldTimerManager().ClearTimer(TimerHandle_LifeSpanExpired);
}



void AFlyObject::OnSphereOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	//IPickUpInterface* PickupInterface = Cast<IPickUpInterface>(OtherActor);
	if (OtherActor)
	{
		//PickUpSystem();
		//PickUpSound();
		if (!OtherActor->ActorHasTag(FName("EngageableTarget"))) {
			UGameplayStatics::ApplyDamage(OtherActor, Damage, GetInstigator()->GetController(), this, UDamageType::StaticClass());
			ExcuteGetHit(OtherActor);
			Destroy();
			PickUpSystem();
			PickUpSound();
		}
		
	}

}



void AFlyObject::ExcuteGetHit(AActor* OtherActor)
{
	IHitInterface* HitInterface = Cast<IHitInterface>(OtherActor);
	if (HitInterface) {
		HitInterface->Execute_GetHit(OtherActor, OtherActor->GetActorLocation(), GetOwner());
	}
}

void AFlyObject::setDamage(float MagicPower)
{
	Damage += MagicPower;
}
