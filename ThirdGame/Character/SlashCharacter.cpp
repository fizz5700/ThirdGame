

#include "SlashCharacter.h"
#include "ThirdGame/Item.h"
#include "ThirdGame/Weapon.h"
#include "Animation/AnimMontage.h"
#include "Components/BoxComponent.h"

class UEmhancedInputlocalPlayerSubsystem;
class UEnhancedInputComponent;
class AEISCppCharacter;
ASlashCharacter::ASlashCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ASlashCharacter::DisArm()
{
	if (EquippedWeapon) {
		EquippedWeapon->AttachMeshToSocket(GetMesh(), FName("SpineSocket"));
	}
	
}

void ASlashCharacter::Arm()
{
	if (EquippedWeapon) {
		EquippedWeapon->AttachMeshToSocket(GetMesh(), FName("RightHandSocket"));
	}
}

void ASlashCharacter::EnableWeaponCollision(ECollisionEnabled::Type CollisionEnabled)
{
	if (EquippedWeapon) {
		EquippedWeapon->GetWeaponBox()->SetCollisionEnabled(CollisionEnabled);
	}
}

void ASlashCharacter::DisableWeaponCollision(ECollisionEnabled::Type CollisionDisabled)
{
	if (EquippedWeapon&&EquippedWeapon->GetWeaponBox()) {
		EquippedWeapon->GetWeaponBox()->SetCollisionEnabled(CollisionDisabled);
		EquippedWeapon->IgnoreActors.Empty();
	}
}

void ASlashCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASlashCharacter::AttackEnd()
{
	ActionState = EActionState::EAS_Unoccupied;
}

void ASlashCharacter::FinishArm()
{
	ActionState = EActionState::EAS_Unoccupied;
}

void ASlashCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASlashCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//check(PlayerInputComponent);
	//if (APlayerController* PC = CastChecked<APlayerController>(GetController())) {
	//	if (UEmhancedInputlocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEmhancedInputlocalPlayerSubsystem>(PC->GetLocalPlayer()))
	//		Subsystem->AddMappingContext(IMC_Action, 0);
	//}
	//
	//if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)){
	//	if (IA_Attack) {
	//		EnhancedInputComponent->BindAction(IA_Attack, ETriggerEvent::Trigered, this, &AEISCppCharacter::MoveForward);
	//	}
	//}
	//PlayerInputComponent->BindAction(FName("Attack"),IE_Pressed,this,&ASlashCharacter::Attack);
}

void ASlashCharacter::EKeyPressed()
{
	AWeapon* OverlappingWeapon = Cast<AWeapon>(OverlappingItem);
	if (OverlappingWeapon) {
		OverlappingWeapon->Equip(GetMesh(), FName("RightHandSocket"),this,this);
		CharacterState = ECharacterState::ECS_EquippedOneHandedWeapon;
		OverlappingItem = nullptr;
		EquippedWeapon = OverlappingWeapon;
	}else {
		if (CanDisarm()) {
			PlayEquipMontage(FName("UnEquip"));
			CharacterState = ECharacterState::ECS_Unequipped;
			ActionState = EActionState::EAS_EquippingWeapon;

		}else if (CanArm()) {
			PlayEquipMontage(FName("Equip"));
			CharacterState = ECharacterState::ECS_EquippedOneHandedWeapon;
			ActionState = EActionState::EAS_EquippingWeapon;
		}
		//OverlappingItem = nullptr;
	}
}

bool ASlashCharacter::CanDisarm()
{
	return ActionState == EActionState::EAS_Unoccupied &&
		CharacterState != ECharacterState::ECS_Unequipped;
}

bool ASlashCharacter::CanArm()
{
	return ActionState == EActionState::EAS_Unoccupied &&
		CharacterState == ECharacterState::ECS_Unequipped &&
		EquippedWeapon;
}

void ASlashCharacter::Attack()
{
	if (ActionState == EActionState::EAS_Unoccupied&& CharacterState!=ECharacterState::ECS_Unequipped) {
		PlayAttackMontage();
		ActionState = EActionState::EAS_Attacking;
	}
	
}

void ASlashCharacter::PlayAttackMontage()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && AttackMontage) {
		AnimInstance->Montage_Play(AttackMontage);
		const int32 Selection = FMath::RandRange(0, 1);
		FName SectionName = FName();
		switch (Selection) {
		case 0:
			SectionName = FName("Attack1");
			break;
		case 1:
			SectionName = FName("Attack2");
			break;
		default:
			break;
		}
		AnimInstance->Montage_JumpToSection(SectionName, AttackMontage);
	}
}

void ASlashCharacter::PlayEquipMontage(FName SectionName)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && EquipMontage) {
		AnimInstance->Montage_Play(EquipMontage);
		AnimInstance->Montage_JumpToSection(SectionName, EquipMontage);
	}
}
