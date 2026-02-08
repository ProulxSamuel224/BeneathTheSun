// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Components/ShapeComponent.h"
#include "Components/SphereComponent.h"
#include "BTS/GAS/AttributeSets/PlayerAttributeSet.h"
#include "BTS/GAS/BTSAbilitySystemComponent.h"

#include "BTS/Combat/WeaponActor.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "BTS/GameFramework/UGameManager.h"


// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	CollisionShape = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionShape"));

	RootComponent = CollisionShape;

	PlayerPawnController = CreateDefaultSubobject<APlayerPawnController>("PlayerController", false);
	PlayerPawnController->SetPawn(this);
	PlayerPawnController->SetAsLocalPlayerController();

	StaticMesh->SetupAttachment(RootComponent);

	AbilitySystemComponent = CreateDefaultSubobject<UBTSAbilitySystemComponent>("AbilitySystemComponent", false);

	PlayerAttributeSet = CreateDefaultSubobject<UPlayerAttributeSet>(TEXT("PlayerAttributes"));
	ShipAttributeSet = CreateDefaultSubobject<UShipAttributeSet>(TEXT("ShipAttributes"));
	WeaponOneAttachPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Weapon One"));
	WeaponTwoAttachPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Weapon Two"));
	WeaponOneAttachPoint->SetupAttachment(RootComponent);
	WeaponTwoAttachPoint->SetupAttachment(RootComponent);

}

void APlayerPawn::AddLooseGameplayTag(FGameplayTag InTag) const
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->AddLooseGameplayTag(InTag);
	}
}


void APlayerPawn::RemoveLooseGameplayTag(FGameplayTag InTag) const
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->RemoveLooseGameplayTag(InTag);
	}
}


void APlayerPawn::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	if (IsValid(AbilitySystemComponent))
	{
		AbilitySystemComponent->GetOwnedGameplayTags(TagContainer);
	}
}


bool APlayerPawn::HasMatchingGameplayTag(FGameplayTag TagToCheck) const
{
	return AbilitySystemComponent && AbilitySystemComponent->HasMatchingGameplayTag(TagToCheck);
}


bool APlayerPawn::HasAllMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const
{
	return AbilitySystemComponent && AbilitySystemComponent->HasAllMatchingGameplayTags(TagContainer);
}


bool APlayerPawn::HasAnyMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const
{
	return AbilitySystemComponent && AbilitySystemComponent->HasAnyMatchingGameplayTags(TagContainer);
}

UAbilitySystemComponent* APlayerPawn::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	CollisionShape->OnComponentHit.AddDynamic(this, &APlayerPawn::OnCollisionHit);




	if (IsValid(AbilitySystemComponent))
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		AbilitySystemComponent->AddAttributeSetSubobject(PlayerAttributeSet);
		AbilitySystemComponent->AddAttributeSetSubobject(ShipAttributeSet);

		AbilitySystemComponent->InitializeComponent();

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UShipAttributeSet::GetHullAttribute()).AddUObject(this, &APlayerPawn::OnHullChanged);
		
	}

	if (IsValid(WeaponSlotOne))
	{
		EquippedWeaponOne = EquipWeapon(WeaponOneAttachPoint, WeaponSlotOne);
	}
	if (IsValid(WeaponSlotTwo))
	{
		EquippedWeaponTwo = EquipWeapon(WeaponTwoAttachPoint, WeaponSlotTwo);
	}

	SwitchWeapon();
}

void APlayerPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{

	Super::EndPlay(EndPlayReason);
}

void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{

		Subsystem->ClearAllMappings();
		Subsystem->AddMappingContext(DefaultMappingContext, 0);

		UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);

		Input->BindAction(MoveUpAction, ETriggerEvent::Completed, this, &APlayerPawn::MoveUp);
		Input->BindAction(MoveDownAction, ETriggerEvent::Completed, this, &APlayerPawn::MoveDown);
		Input->BindAction(TargetUpAction, ETriggerEvent::Completed, this, &APlayerPawn::TargetUp);
		Input->BindAction(TargetDownAction, ETriggerEvent::Completed, this, &APlayerPawn::TargetDown);
		Input->BindAction(SwitchWeaponAction, ETriggerEvent::Completed, this, &APlayerPawn::SwitchWeapon);

		for (const auto& ActivableAbility : ActivableAbilities)
		{
			AbilitySystemComponent->GiveAbility(ActivableAbility.Value);
			UInputAction* InputAction = ActivableAbility.Key;
			if (InputAction)
			{
				Input->BindAction(InputAction, ETriggerEvent::Completed, this, &APlayerPawn::ActivateAbilityFromInput, InputAction);
			}
		}

	}
}

void APlayerPawn::MoveUp(const FInputActionValue& Value)
{
	if (bIsMoving)
	{
		return;
	}
	UUGameManager* GameManager = GetGameInstance()->GetSubsystem<UUGameManager>();

	EMovementType MovementType = EMovementType::MoveUp;
	if (IsValid(GameManager))
	{
		GameManager->MovePlayerPawnOnCorridor(MovementType);
	}

	OnPawnMoved(true);
	GEngine->AddOnScreenDebugMessage(3, 10, FColor::Red, "MoveUp", false);
}

void APlayerPawn::MoveDown(const FInputActionValue& Value)
{

	if (bIsMoving)
	{
		return;
	}
	UUGameManager* GameManager = GetGameInstance()->GetSubsystem<UUGameManager>();

	EMovementType MovementType = EMovementType::MoveDown;

	if (IsValid(GameManager))
	{
		GameManager->MovePlayerPawnOnCorridor(MovementType);
	}
	OnPawnMoved(false);
	GEngine->AddOnScreenDebugMessage(3, 10, FColor::Red, "MoveDown", false);
}

void APlayerPawn::TargetUp(const FInputActionValue& Value)
{
	UUGameManager* GameManager = GetGameInstance()->GetSubsystem<UUGameManager>();

	GameManager->UpdateTargettedCorridor(true);
	GEngine->AddOnScreenDebugMessage(3, 10, FColor::Red, "SelectTargetUp", false);
}
void APlayerPawn::TargetDown(const FInputActionValue& Value)
{
	UUGameManager* GameManager = GetGameInstance()->GetSubsystem<UUGameManager>();

	GameManager->UpdateTargettedCorridor(false);
	GEngine->AddOnScreenDebugMessage(3, 10, FColor::Red, "SelectTargetDown", false);
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (MovementAlpha > 1)
	{
		bIsMoving = false;
		MovementAlpha = 0;
		MoveToTargetLocation = FVector::ZeroVector;
		MoveToInitiallocation = FVector::ZeroVector;
	}

	if (bIsMoving)
	{
		SetActorLocation(FMath::Lerp(MoveToInitiallocation, MoveToTargetLocation, MovementAlpha));
		MovementAlpha += MoveToSpeed * DeltaTime;
	}
}


void APlayerPawn::OnCollisionHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(2, 10, FColor::Blue, "PlayerPawn Hit");
}

void APlayerPawn::OnPawnDied()
{
	GEngine->AddOnScreenDebugMessage(3, 10, FColor::Blue, "PlayerPawn Dead");
}



void APlayerPawn::SetAttributeSetChangeDelegates()
{

}

void APlayerPawn::OnHullChanged(const FOnAttributeChangeData& Data)
{
	float NewHealth = Data.NewValue;
	float OldHealth = Data.OldValue;

	UE_LOG(LogTemp, Log, TEXT("Health changed from %f to %f"), OldHealth, NewHealth);
	GEngine->AddOnScreenDebugMessage(3, 10, FColor::Blue, "Old Health" + FString::SanitizeFloat(OldHealth));
	GEngine->AddOnScreenDebugMessage(4, 10, FColor::Blue, "New Health" + FString::SanitizeFloat(NewHealth));

}

const float APlayerPawn::GetHullAttributeValue()
{
	if (IsValid(ShipAttributeSet))
	{
		return ShipAttributeSet->GetHullAttribute().GetNumericValue(ShipAttributeSet);
	}
	return 0.f;
}	

void APlayerPawn::MoveToLocation(FVector NewLocation)
{
	if (IsValid(PlayerAttributeSet))
	{
		//float PilotingSkillValue = 	PlayerAttributeSet->GetPilotingAttribute().GetNumericValue(PlayerAttributeSet);

		//MoveToSpeed += (PilotingSkillValue / 10);
		
		MoveToTargetLocation = NewLocation;
		MoveToInitiallocation = GetActorLocation();
		bIsMoving = true;
	}
}

void APlayerPawn::ActivateAbilityFromInput(const FInputActionValue& Value, UInputAction* InputAction)
{
	if (AbilitySystemComponent && InputAction && ActivableAbilities.Contains(InputAction))
	{
		TSubclassOf<UBTSGameplayAbility> AbilityClass = ActivableAbilities[InputAction];
		if (AbilityClass)
		{
			if (AbilitySystemComponent->HasAbility(AbilityClass))
			{
				AbilitySystemComponent->TryActivateAbility(AbilitySystemComponent->GetGrantedAbilitySpecHandle(AbilityClass));
			}
		}
	}
}

AWeaponActor* APlayerPawn::EquipWeapon(USceneComponent* AttachPoint, TSubclassOf<AWeaponActor> Weapon)
{
	FActorSpawnParameters Params;
	
	AWeaponActor* SpawnedWeapon = GetWorld()->SpawnActor<AWeaponActor>( Weapon,AttachPoint->GetComponentLocation(), AttachPoint->GetComponentRotation(), Params);

	
	SpawnedWeapon->AttachToComponent(AttachPoint, FAttachmentTransformRules::SnapToTargetIncludingScale);

	if (SpawnedWeapon != nullptr)
	{
		return SpawnedWeapon;
	}

	return nullptr;
}

void APlayerPawn::SwitchWeapon()
{
	if ((EquippedWeaponOne == nullptr) && (EquippedWeaponTwo== nullptr))
	{
		
		GEngine->AddOnScreenDebugMessage(3, 10, FColor::Blue, "No Weapon");
		return;
	}

	if (EquippedWeaponOne == nullptr)
	{
		SelectedWeapon = EquippedWeaponTwo;
	}
	
	if (EquippedWeaponTwo == nullptr)
	{
		SelectedWeapon = EquippedWeaponOne;
	}

	if (SelectedWeapon == EquippedWeaponOne)
	{
		SelectedWeapon = EquippedWeaponTwo;
	}
	else
	{
		SelectedWeapon = EquippedWeaponOne;
	}
}


AWeaponActor* APlayerPawn::GetSelectedWeapon()
{
	if (SelectedWeapon != nullptr)
	{
		return SelectedWeapon;
	}
	return nullptr;
}

