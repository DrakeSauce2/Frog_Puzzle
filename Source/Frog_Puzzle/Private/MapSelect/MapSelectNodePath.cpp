// Fill out your copyright notice in the Description page of Project Settings.


#include "MapSelect/MapSelectNodePath.h"
#include "MapSelect/LevelNode.h"

#include "Components/SplineComponent.h"
#include "Engine/World.h"

AMapSelectNodePath::AMapSelectNodePath()
{
	PrimaryActorTick.bCanEverTick = true;

	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("PathSpline"));
	RootComponent = Spline;
}

void AMapSelectNodePath::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMapSelectNodePath::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMapSelectNodePath::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    // Step 1: Cache current spline point positions
    CachedNodePositions.Empty();
    if (Spline)
    {
        for (int32 i = 0; i < Spline->GetNumberOfSplinePoints(); ++i)
        {
            CachedNodePositions.Add(Spline->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World));
        }
    }

    // Step 2: Clear old nodes and spline points
    ClearExistingNodes(); // Just clears actors and spline, not our CachedNodePositions

    // Step 3: Rebuild based on LevelNames
    for (int32 i = 0; i < LevelNames.Num(); ++i)
    {
        FVector SpawnLocation;

        // Use previous location if available
        if (CachedNodePositions.IsValidIndex(i))
        {
            SpawnLocation = CachedNodePositions[i];
        }
        else
        {
            SpawnLocation = GetActorLocation() + FVector(i * 300.f, 0.f, 0.f); // Default position
        }

        FActorSpawnParameters Params;
        Params.Owner = this;

        ALevelNode* Node = GetWorld()->SpawnActor<ALevelNode>(NodeClass, SpawnLocation, FRotator::ZeroRotator, Params);
        if (Node)
        {
            Node->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
            Node->InitializeNode(i, this);
            SpawnedNodes.Add(Node);

            Spline->AddSplinePoint(Node->GetActorLocation(), ESplineCoordinateSpace::World);
        }
    }

    Spline->UpdateSpline();
}

void AMapSelectNodePath::UpdateSplinePoint(int32 Index, const FVector& NewLocation)
{
    if (Spline && Index < Spline->GetNumberOfSplinePoints())
    {
        Spline->SetLocationAtSplinePoint(Index, NewLocation, ESplineCoordinateSpace::World);
        Spline->UpdateSpline();
    }
}

void AMapSelectNodePath::ClearExistingNodes()
{
    for (AActor* Node : SpawnedNodes)
    {
        if (Node && !Node->IsPendingKillPending())
        {
            Node->Destroy();
        }
    }

    SpawnedNodes.Empty();
    if (Spline)
    {
        Spline->ClearSplinePoints(false);
    }
}


