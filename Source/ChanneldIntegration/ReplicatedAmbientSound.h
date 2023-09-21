#pragma once

#include "CoreMinimal.h"
#include "Sound/AmbientSound.h"
#include "ReplicatedAmbientSound.generated.h"

/**
 * Sound actor that can replicate the Sound property of its AudioComponent.
 */
UCLASS(Blueprintable, meta=(ChildCanTick))
class CHANNELDINTEGRATION_API AReplicatedAmbientSound : public AAmbientSound
{
	GENERATED_BODY()
	
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;

private:
	UPROPERTY(ReplicatedUsing=OnRep_Sound, transient)
	USoundBase* ReplicatedSound;

public:
	UFUNCTION(BlueprintCallable)
	void SetReplicatedSound(USoundBase* InSound);

	UFUNCTION()
	void OnRep_Sound();
};
