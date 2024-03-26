#pragma once

#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"
#include "TestAbilitySet.generated.h"

UENUM(BlueprintType)
enum class EAbilityInput : uint8
{
	None = 0 UMETA(Hidden),
	Jump = 1,
	Primary = 2,
	Secondary = 3,
};

USTRUCT()
struct FAbilitySetItem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "GAS")
	TSubclassOf<UGameplayAbility> Ability;

	UPROPERTY(EditDefaultsOnly, Category = "GAS")
	EAbilityInput InputKey;
};

UCLASS()
class CHANNELDINTEGRATION_API UTestAbilitySet : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "GAS")
	TArray<FAbilitySetItem> AbilitySetItems;

	TArray<FGameplayAbilitySpecHandle> GrantAbilitiesToAbilitySystem(UAbilitySystemComponent* AbilitySystemComponent) const
	{
		TArray<FGameplayAbilitySpecHandle> Handle;
		for (const FAbilitySetItem& Item : AbilitySetItems)
		{
			FGameplayAbilitySpecHandle NewHandle = AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Item.Ability.GetDefaultObject(), 0, static_cast<uint32>(Item.InputKey)));
			Handle.AddUnique(NewHandle);
		}
		return Handle;
	}
};