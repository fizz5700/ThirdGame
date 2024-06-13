

#include "Weapon.h"
#include "Character/SlashCharacter.h"


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
	FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
	ItemMesh->AttachToComponent(InParent, TransformRules, InSocketName);
}
