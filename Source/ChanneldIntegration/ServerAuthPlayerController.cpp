#include "ServerAuthPlayerController.h"

#include "Net/UnrealNetwork.h"

void AServerAuthPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(AServerAuthPlayerController, PlayerAlias, COND_InitialOnly);
}
