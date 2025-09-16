// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelNode.generated.h"

UCLASS()
class ALevelNode : public AActor
{
	GENERATED_BODY()
	
public:	
	ALevelNode();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

public:	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	void InitializeNode(const int32& Index, class AMapSelectNodePath* MapSelectOwner);

private:
	UPROPERTY()
	int32 NodeIndex;

	UPROPERTY()
	class AMapSelectNodePath* OwnerMap;
};
