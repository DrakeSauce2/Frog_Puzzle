// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapSelectNodePath.generated.h"

class ALevelNode;
UCLASS()
class AMapSelectNodePath : public AActor
{
	GENERATED_BODY()
	
public:	
	AMapSelectNodePath();

    virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
    virtual void OnConstruction(const FTransform& Transform) override;

public:	
    UPROPERTY(EditAnywhere, Category = "Path")
    class USplineComponent* Spline;

    UPROPERTY(EditAnywhere, Category = "Path")
    TArray<FName> LevelNames;

    UPROPERTY(EditAnywhere, Category = "Path")
    TSubclassOf<ALevelNode> NodeClass;

    UPROPERTY()
    TArray<ALevelNode*> SpawnedNodes;

    void UpdateSplinePoint(int32 Index, const FVector& NewLocation);

private:
    void ClearExistingNodes();
    TArray<FVector> CachedNodePositions;

};
