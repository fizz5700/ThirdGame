
#include "Item.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "ThirdGame/Interfaces/PickUpInterface.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	ItemMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetRootComponent(ItemMesh);

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere ->SetupAttachment(GetRootComponent());

	ItemEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("EmbersEffect"));
	ItemEffect->SetupAttachment(GetRootComponent());

}	
void AItem::OnSphereOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IPickUpInterface* PickUpInterface = Cast<IPickUpInterface>(OtherActor);
	UE_LOG(LogTemp,Warning,TEXT("iTEM OnSphereOverlap START"));
	if (PickUpInterface) {
		UE_LOG(LogTemp, Warning, TEXT("iTEM OnSphereOverlap PickUpInterface EXSIES"));
		PickUpInterface->SetOverlappingItem(this);
	}
}

void AItem::OnSphereEndOverlap(class UPrimitiveComponent* OnComponentEndOverlap,  class AActor* OtherActor,  class UPrimitiveComponent*  OtherComp, int32  OtherBodyIndex)
{
	IPickUpInterface* PickUpInterface = Cast<IPickUpInterface>(OtherActor);
	if (PickUpInterface) {
		PickUpInterface->SetOverlappingItem(nullptr);
	}

}

void AItem::PickUpSystem()
{
	if (PcikUpEffect) {
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			this,
			PcikUpEffect,
			GetActorLocation()
		);
	}
}

void AItem::PickUpSound()
{
	
		if (PcikUpSound) {
			UGameplayStatics::PlaySoundAtLocation(
				this,
				PcikUpSound,
				GetActorLocation()
			);
		}
}



void AItem::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnSphereOverlap);

	Sphere->OnComponentEndOverlap.AddDynamic(this, &AItem::OnSphereEndOverlap);
	
}
float AItem::TransformedSin()
{
	return Amplitude * FMath::Sin(RunningTime * TimeConstant);
}


void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RunningTime += DeltaTime;
	if (ItemState == EItemState::EIS_Hovering) {
		AddActorWorldOffset(FVector(0.f, 0.f, TransformedSin()));
	}
}


 

