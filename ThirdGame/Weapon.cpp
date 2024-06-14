

#include "Weapon.h"
#include "Character/SlashCharacter.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"


void AWeapon::OnSphereOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	//ASlashCharacter* SlashCharacter=Cast<ASlashCharacter>(OtherActor);
	//if (SlashCharacter) {
	//	FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
	//	ItemMesh->AttachToComponent(SlashCharacter->GetMesh(), TransformRules,FName("RightHandSocket"));
	//}

}

void AWeapon::OnSphereEndOverlap(UPrimitiveComponent* OnComponentEndOverlap, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnSphereEndOverlap(OnComponentEndOverlap, OtherActor, OtherComp, OtherBodyIndex);
}

void AWeapon::Equip(USceneComponent* InParent, FName InSocketName)
{
	AttachMeshToSocket(InParent, InSocketName);
	ItemState = EItemState::EIS_Equipped;
	if (EquipSound) {
		UGameplayStatics::PlaySoundAtLocation(this,EquipSound,GetActorLocation());
	}
	if (Sphere) {
		Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void AWeapon::AttachMeshToSocket(USceneComponent* InParent, const FName& InSocketName)
{
	FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
	ItemMesh->AttachToComponent(InParent, TransformRules, InSocketName);
}
