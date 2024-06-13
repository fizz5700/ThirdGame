
#include "Item.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Character/SlashCharacter.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	SetRootComponent(ItemMesh);

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere ->SetupAttachment(GetRootComponent());

	// 创建BoxComponent
	//MyBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("MyBoxComponent"));

	
}	
void AItem::OnSphereOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASlashCharacter* SlashCharacter = Cast<ASlashCharacter>(OtherActor);
	if (SlashCharacter) {
		SlashCharacter->SetOverlappingItem(this);
	}
}

void AItem::OnSphereEndOverlap(class UPrimitiveComponent* OnComponentEndOverlap,  class AActor* OtherActor,  class UPrimitiveComponent*  OtherComp, int32  OtherBodyIndex)
{
	//const FString OtherActorName = FString("OnSphereOverlap :") + OtherActor->GetName();
	//if (GEngine) {
	//	GEngine->AddOnScreenDebugMessage(1, 30.f, FColor::Blue, OtherActorName);
	//}
	ASlashCharacter* SlashCharacter = Cast<ASlashCharacter>(OtherActor);
	if (SlashCharacter) {
		SlashCharacter->SetOverlappingItem(nullptr);
	}

}



void AItem::BeginPlay()
{
	Super::BeginPlay();

	// 注册事件响应函数onComponentBeginOverlap
	//MyBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AItem::NotifyActorBeginOverlap);
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


 

