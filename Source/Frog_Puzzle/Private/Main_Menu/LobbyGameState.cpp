// Fill out your copyright notice in the Description page of Project Settings.


#include "Main_Menu/LobbyGameState.h"
#include "Main_Menu/LobbyPlayerState.h"

bool ALobbyGameState::AreAllPlayersReady() const
{
    for (APlayerState* PlayerState : PlayerArray)
    {
        ALobbyPlayerState* LobbyPS = Cast<ALobbyPlayerState>(PlayerState);
        if (!LobbyPS || !LobbyPS->bIsReady)
        {
            return false;
        }
    }

    return true;
}


void ALobbyGameState::AddPlayerState(APlayerState* PlayerState)
{
    Super::AddPlayerState(PlayerState);
    OnLobbyPlayersChanged.Broadcast();
}

void ALobbyGameState::RemovePlayerState(APlayerState* PlayerState)
{
    Super::RemovePlayerState(PlayerState);
    OnLobbyPlayersChanged.Broadcast();
}