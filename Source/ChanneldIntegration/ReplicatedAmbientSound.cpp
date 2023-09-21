#include "ReplicatedAmbientSound.h"

#include "Components/AudioComponent.h"
#include "Net/UnrealNetwork.h"

void AReplicatedAmbientSound::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AReplicatedAmbientSound, ReplicatedSound);
}

void AReplicatedAmbientSound::SetReplicatedSound(USoundBase* InSound)
{
	ReplicatedSound = InSound;
	GetAudioComponent()->Sound = ReplicatedSound;
}

void AReplicatedAmbientSound::OnRep_Sound()
{
	if (auto Comp = GetAudioComponent())
	{
		Comp->Sound = ReplicatedSound;
		Comp->Play();
	}
}
