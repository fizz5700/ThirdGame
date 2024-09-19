// Fill out your copyright notice in the Description page of Project Settings.


#include "ThirdGame/Inventory/ItemActor.h"


#include "Components/SphereComponent.h"
#include "ThirdGame/Inventory/InventoryComponent.h"
#include "ThirdGame/Character/SlashCharacter.h"

// Sets default values
AItemActor::AItemActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(MeshComponent);
	SphereComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AItemActor::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AItemActor::BeginPlay()
{
	Super::BeginPlay();

	if (ItemObject == nullptr)
	{
		ItemObject = GetDefaultItemObject();
	}
}

//UItemObject* AItemActor::GetDefaultItemObject()
//{
//	//ItemObject->InitializeItemObject(1,1,);
//
//	return ItemObject;
//}


void AItemActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp,Warning,TEXT("AItemActor::OnOverlapBegin"));
	ASlashCharacter* Player = Cast<ASlashCharacter>(OtherActor);
	if (Player->GetInventoryComponent()->TryAddItem(ItemObject))
	{
			Destroy();
	}
}

