// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "LobbyPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class ALobbyPlayerState : public APlayerState
{
    GENERATED_BODY()

public:
    ALobbyPlayerState();

    /** Whether the player is ready */
    UPROPERTY(ReplicatedUsing = OnRep_IsReady)
    bool bIsReady;

    /** Called when bIsReady changes */
    UFUNCTION()
    void OnRep_IsReady();

    /** Called by UI to toggle ready */
    UFUNCTION(Server, Reliable)
    void Server_SetReady(bool bReady);

protected:
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
