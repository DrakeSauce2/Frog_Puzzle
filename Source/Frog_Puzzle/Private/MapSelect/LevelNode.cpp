#include "MapSelect/LevelNode.h"
#include "MapSelect/MapSelectNodePath.h"

ALevelNode::ALevelNode()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Node Mesh"));
	RootComponent = Mesh;
}

void ALevelNode::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALevelNode::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (OwnerMap)
	{
		OwnerMap->UpdateSplinePoint(NodeIndex, GetActorLocation());
	}
}

void ALevelNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelNode::InitializeNode(const int32& Index, AMapSelectNodePath* MapSelectOwner)
{
	NodeIndex = Index;
	OwnerMap = MapSelectOwner;
}
