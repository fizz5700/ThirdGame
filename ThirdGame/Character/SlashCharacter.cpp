

#include "SlashCharacter.h"
#include "ThirdGame/Item.h"
#include "ThirdGame/Weapon.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GroomComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ThirdGame/Components/AttributeComponent.h"
#include "Animation/AnimMontage.h"
#include "ThirdGame/HUD/SlashHUD.h"
#include "ThirdGame/HUD/SlashOverlay.h"
#include "ThirdGame/Interfaces/PickUpInterface.h"
#include "ThirdGame/Soul.h"
#include "ThirdGame/Treasure.h"
#include "ThirdGame/Inventory/InventoryComponent.h"

#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

class USpringArmComponent;
class UCameraComponent;
class UGroomComponent;
class AItem;
class ASoul;
class ATreasure;
class UAnimMontage;
class USlashOverlay;
class AFlyObject;

ASlashCharacter::ASlashCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	GetMesh()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);

	Hair = CreateDefaultSubobject<UGroomComponent>(TEXT("Hair"));
	Hair->SetupAttachment(GetMesh());
	Hair->AttachmentName = FString("head");

	Eyebrows = CreateDefaultSubobject<UGroomComponent>(TEXT("Eyebrows"));
	Eyebrows->SetupAttachment(GetMesh());
	Eyebrows->AttachmentName = FString("head");

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);


	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); 
	FollowCamera->bUsePawnControlRotation = false; 

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

void ASlashCharacter::DisableWeaponCollision(ECollisionEnabled::Type CollisionDisabled)
{
	if (EquippedWeapon) {
		EquippedWeapon->GetWeaponBox()->SetCollisionEnabled(CollisionDisabled);
	}
}

float ASlashCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	HandleDamage(DamageAmount);
	SetHUDHealth();
	return DamageAmount;

}

void ASlashCharacter::SetOverlappingItem(AItem* Item)
{
	OverlappingItem = Item;
}

void ASlashCharacter::AddSouls(ASoul* Soul)
{
	if (SlashOverlay && Attributes) {
		//SlashOverlay->SetSoulsText(1);
		Attributes->AddSouls(Soul->GetSouls());
		SlashOverlay->SetSoulsText(Attributes->GetSouls());
	}
}

void ASlashCharacter::AddGold(ATreasure* Treasure)
{
	if (SlashOverlay && Attributes) {

		Attributes->AddGold(Treasure->GetGold());
		SlashOverlay->SetGoldText(Attributes->GetGold());
		
	}
}

bool ASlashCharacter::ReduceCureTimes()
{
	bool ifSuccess=false;
	if (SlashOverlay && Attributes) {
		UE_LOG(LogTemp, Warning, TEXT("BOTH HAVE"));
		ifSuccess = Attributes->UseCureTimes();
		if (ifSuccess) {
			UE_LOG(LogTemp, Warning, TEXT("BOTH HAVE  ifSuccess"));
		}
		
		SlashOverlay->SetCureTimes(Attributes->GetCureRemainTimes());
	}
	return ifSuccess;

	
}

void ASlashCharacter::SetHUDHealth()
{
	if (SlashOverlay && Attributes) {
		SlashOverlay->SetHealthProgressBar(Attributes->GetHealthPercent());
	}
}

void ASlashCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	Tags.Add(FName("EngageableTarget"));
	InitializeSlashOverlay();
}

void ASlashCharacter::InitializeSlashOverlay()
{
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	Tags.Add(FName("EngageableTarget"));
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		ASlashHUD* SlashHUD = Cast<ASlashHUD>(PlayerController->GetHUD());
		if (SlashHUD)
		{
			SlashOverlay = SlashHUD->GetSlashOverlay();
			if (SlashOverlay && Attributes)
			{
				SlashOverlay->SetHealthProgressBar(Attributes->GetHealthPercent());
				SlashOverlay->SetStaminaProgressBar(1.f);
				SlashOverlay->SetGoldText(0);
				SlashOverlay->SetSoulsText(0);
				SlashOverlay->SetCureTimes(Attributes->GetCureRemainTimes());
			}
		}
	}
}


void ASlashCharacter::AttackEnd()
{
	ActionState = EActionState::EAS_Unoccupied;
}

void ASlashCharacter::FinishArm()
{
	ActionState = EActionState::EAS_Unoccupied;
}

void ASlashCharacter::HitReactEnd()
{
	ActionState = EActionState::EAS_Unoccupied;
}

void ASlashCharacter::Die()
{
	Super::Die();
	ActionState=EActionState::EAS_Dead;
	//GetCharacterMovement()->bOrientRotationToMovement = false;
	//DisableMeshCollision();
	GetWorldTimerManager().SetTimer(ReSpawnTimer, this, &ASlashCharacter::ReSpawn, 5.f);
}
void ASlashCharacter::ReSpawn()
{
	this->SetActorLocation(NearestReSpawnVector);
	Tags.Remove(FName("Dead"));
	//GetCharacterMovement()->bOrientRotationToMovement = true;
	//GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetWorldTimerManager().ClearTimer(ReSpawnTimer);
	if (Attributes && SlashOverlay) {
		Attributes->ResetState();
		SetHUDHealth();
		SlashOverlay->SetCureTimes(Attributes->GetCureRemainTimes());
	}
}

void ASlashCharacter::DisableMeshCollision()
{
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ASlashCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Attributes&& SlashOverlay) {
		Attributes->RegenStamina(DeltaTime);
		SlashOverlay->SetStaminaProgressBar(Attributes->GetStaminaPercent());
	}
}

void ASlashCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
	
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	
		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASlashCharacter::Move);
	
		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASlashCharacter::Look);
	
		//Dodge
		EnhancedInputComponent->BindAction(DodgeAction, ETriggerEvent::Triggered, this, &ASlashCharacter::Dodge);
		
	}
}

void ASlashCharacter::GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter)
{
	Super::GetHit_Implementation(ImpactPoint, Hitter);

	SetWeaponCollisionEnabled(ECollisionEnabled::NoCollision);
	if (Attributes && Attributes->GetHealthPercent() > 0.f)
	{
		ActionState = EActionState::EAS_HitReaction;
	}

}

void ASlashCharacter::Dodge()
{
	if (ActionState != EActionState::EAS_Unoccupied || !HasEnoughStamina(Attributes->GetDodgeCost())) return;
	PlayDodgeMontage();
	ActionState = EActionState::EAS_Dodge;
	if (Attributes && SlashOverlay)
	{
		Attributes->UseStamina(Attributes->GetDodgeCost());
		SlashOverlay->SetStaminaProgressBar(Attributes->GetStaminaPercent());
	}
}
bool ASlashCharacter::HasEnoughStamina(float StaminaCost)
{
	return Attributes && Attributes->GetStamina() > StaminaCost;
}

bool ASlashCharacter::IsOccupied()
{
	return ActionState != EActionState::EAS_Unoccupied;
}


void ASlashCharacter::DodgeEnd()
{
	Super::DodgeEnd();

	ActionState = EActionState::EAS_Unoccupied;
}

void ASlashCharacter::EKeyPressed()
{

	AWeapon* OverlappingWeapon = Cast<AWeapon>(OverlappingItem);
	if (OverlappingWeapon) {
		if (EquippedWeapon)
		{
			EquippedWeapon->Destroy();
		}
		OverlappingWeapon->Equip(GetMesh(), FName("RightHandSocket"),this,this);
		CharacterState = ECharacterState::ECS_EquippedOneHandedWeapon;
		OverlappingItem = nullptr;
		EquippedWeapon = OverlappingWeapon;
	}
	else {
		if (CanDisarm()) {
			PlayEquipMontage(FName("UnEquip"));
			CharacterState = ECharacterState::ECS_Unequipped;
			ActionState = EActionState::EAS_EquippingWeapon;
	
		}else if (CanArm()) {
			PlayEquipMontage(FName("Equip"));
			CharacterState = ECharacterState::ECS_EquippedOneHandedWeapon;
			ActionState = EActionState::EAS_EquippingWeapon;
		}
	}
}
 
void ASlashCharacter::SpawnWindWall()
{
	UWorld* World = GetWorld();
	if (World && WindWallClass) {
		PlayRandomMontageSection(AttackMontage, SkillMontageSections);
		const FVector SpawnLocation = GetActorLocation() + FVector(50.f, 0.f, 0.f);
		AWindWall* SpawnWindWall = World->SpawnActor<AWindWall>(WindWallClass, SpawnLocation, GetActorRotation());
	}
}
void ASlashCharacter::SendFlyObject()
{
	UWorld* World = GetWorld();
	if (World && FlyObjectClass) {
		const FVector SpawnLocation = GetActorLocation() + FVector(150.f, 0.f, 0.f);
		AFlyObject* FlyObject = World->SpawnActor<AFlyObject>(FlyObjectClass, SpawnLocation, GetActorRotation());
		if (FlyObject) {
			FlyObject->SetOwner(this);
			FlyObject->SetInstigator(this);
			FlyObject->setDamage(Attributes->GetMagicPower());
		}
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
	if (CanAttack()) {
		PlayAttackMontage();
		ActionState = EActionState::EAS_Attacking;
	}
	
}


void ASlashCharacter::ReleaseSkills()
{
	ActionState = EActionState::EAS_ReleaseSkills;
}
bool ASlashCharacter::CanAttack()
{
	return ActionState == EActionState::EAS_Unoccupied && CharacterState != ECharacterState::ECS_Unequipped;
}
 

void ASlashCharacter::PlayEquipMontage(FName SectionName)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && EquipMontage) {
		AnimInstance->Montage_Play(EquipMontage);
		AnimInstance->Montage_JumpToSection(SectionName, EquipMontage);
	}
}

void ASlashCharacter::PlayCureMontage(FName SectionName)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && CureMontage) {
		AnimInstance->Montage_Play(CureMontage);
		AnimInstance->Montage_JumpToSection(SectionName, CureMontage);
	}
}


void ASlashCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	if (ActionState != EActionState::EAS_Unoccupied) return;

	FVector2D MovementVector = Value.Get<FVector2D>();
	UE_LOG(LogTemp,Warning,TEXT("Move CALLED"));
	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		UE_LOG(LogTemp, Warning, TEXT("Move is not null"));
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ASlashCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

