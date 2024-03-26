#pragma once

#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "AttributeHelpers.h"

#include "TestAttributeSet.generated.h"

UCLASS()
class CHANNELDINTEGRATION_API UTestAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UPROPERTY(BlueprintReadOnly, Category = "GAS", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UTestAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, Category = "GAS", ReplicatedUsing = OnRep_Damage)
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UTestAttributeSet, Damage);

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth);

	UFUNCTION()
	void OnRep_Damage(const FGameplayAttributeData& OldDamage);
};