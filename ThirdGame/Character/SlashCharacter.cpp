

#include "SlashCharacter.h"
#include "ThirdGame/Item.h"
#include "ThirdGame/Weapon.h"
#include "Animation/AnimMontage.h"
class UEmhancedInputlocalPlayerSubsystem;
class UEnhancedInputComponent;
class AEISCppCharacter;
ASlashCharacter::ASlashCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ASlashCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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
		OverlappingWeapon->Equip(GetMesh(), FName("RightHandSocket"));
		CharacterState = ECharacterState::ECS_EquippedOneHandedWeapon;
		
	}
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
	if (AnimInstance && Attackmontage) {
		AnimInstance->Montage_Play(Attackmontage);
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
		AnimInstance->Montage_JumpToSection(SectionName, Attackmontage);
	}
}

