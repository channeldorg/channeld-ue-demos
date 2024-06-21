#include "TestGASActor.h"

#include "EnhancedInputComponent.h"

ATestGASActor::ATestGASActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<UTestAttributeSet>(TEXT("AttributeSet"));
}

void ATestGASActor::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority())
	{
		if (IsValid(InitialAbilitySet))
		{
			InitialGrantedAbilitySpecHandles.Append(InitialAbilitySet->GrantAbilitiesToAbilitySystem(AbilitySystemComponent));
		}

		if (IsValid(InitialGameplayEffect))
		{
			AbilitySystemComponent->ApplyGameplayEffectToSelf(InitialGameplayEffect->GetDefaultObject<UGameplayEffect>(), 0.0f, AbilitySystemComponent->MakeEffectContext());
		}

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UTestAttributeSet::GetHealthAttribute()).AddUObject(this, &ATestGASActor::OnHealthChanged);
	}
}

void ATestGASActor::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (auto EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		for (const auto& Binding : AbilityInputBindings.Bindings)
		{
			EnhancedInputComponent->BindAction(Binding.InputAction, ETriggerEvent::Triggered, this, &ATestGASActor::OnAbilityInputPressed, Binding.AbilityInput);
			EnhancedInputComponent->BindAction(Binding.InputAction, ETriggerEvent::Completed, this, &ATestGASActor::OnAbilityInputCompleted, Binding.AbilityInput);
		}
	}
}

void ATestGASActor::OnHealthChanged(const FOnAttributeChangeData& ChangeData)
{
	this->TeleportTo(this->GetActorLocation() + FVector(0, 0, ChangeData.NewValue - ChangeData.OldValue), FRotator::ZeroRotator, false, false);
	OnHealthChanged(ChangeData.OldValue, ChangeData.NewValue);
}

void ATestGASActor::OnAbilityInputPressed(EAbilityInput AbilityInput)
{
	AbilitySystemComponent->AbilityLocalInputPressed(static_cast<uint32>(AbilityInput));
}

void ATestGASActor::OnAbilityInputCompleted(EAbilityInput AbilityInput)
{
	AbilitySystemComponent->AbilityLocalInputReleased(static_cast<uint32>(AbilityInput));
}
