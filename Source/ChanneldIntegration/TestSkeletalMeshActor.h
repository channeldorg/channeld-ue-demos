#pragma once

#include "CoreMinimal.h"
#include "Animation/SkeletalMeshActor.h"
#include "TestSkeletalMeshActor.generated.h"

/**
 * SkeletalMeshActor replicates its SkeletalMeshComponent's SkeletalMesh property via ReplicatedMesh, but
 * ReplicatedMesh property is not exposed to blueprint. This class adds a function to set the ReplicatedMesh.
 */
UCLASS(Blueprintable)
class CHANNELDINTEGRATION_API ATestSkeletalMeshActor : public ASkeletalMeshActor
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetReplicatedMesh(USkeletalMesh* InSkelMesh);
};
