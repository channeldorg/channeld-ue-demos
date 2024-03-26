#pragma once
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "InputAction.h"
#include "TestAbilitySet.h"
#include "TestAttributeSet.h"

#include "TestGASActor.generated.h"

USTRUCT()
struct FAbilityInputToInputActionBinding
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "GAS")
	UInputAction* InputAction;

	UPROPERTY(EditDefaultsOnly, Category = "GAS")
	EAbilityInput AbilityInput;
};

USTRUCT()
struct FAbilityInputBindings		
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "GAS")
	TArray<FAbilityInputToInputActionBinding> Bindings;
};

UCLASS()
class CHANNELDINTEGRATION_API ATestGASActor : public APawn, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ATestGASActor(const FObjectInitializer& ObjectInitializer);

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override
	{
		return AbilitySystemComponent;
	}

	UPROPERTY(EditDefaultsOnly, Category = "GAS")
	UTestAbilitySet* InitialAbilitySet;

	UPROPERTY(EditDefaultsOnly, Category = "GAS")
	TSubclassOf<UGameplayEffect> InitialGameplayEffect;

	UPROPERTY(EditDefaultsOnly, Category = "GAS")
	FAbilityInputBindings AbilityInputBindings;

	virtual void BeginPlay() override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(BlueprintReadOnly)
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
	UTestAttributeSet* AttributeSet;

	UPROPERTY()
	TArray<FGameplayAbilitySpecHandle> InitialGrantedAbilitySpecHandles;

	void OnHealthChanged(const FOnAttributeChangeData& OnAttributeChangeData);

	UFUNCTION(BlueprintImplementableEvent)
	void OnHealthChanged(float OldValue, float NewValue);
	
	void OnAbilityInputPressed(EAbilityInput AbilityInput);	
	void OnAbilityInputCompleted(EAbilityInput AbilityInput);	

};