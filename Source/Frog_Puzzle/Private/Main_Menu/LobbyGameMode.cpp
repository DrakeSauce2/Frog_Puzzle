// Fill out your copyright notice in the Description page of Project Settings.


#include "Main_Menu/LobbyGameMode.h"
#include "Main_Menu/LobbyGameState.h"
#include "Main_Menu/LobbyPlayerState.h"

#include "Kismet/GameplayStatics.h"

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    // You can log or display player name here
    if (APlayerState* PS = NewPlayer->GetPlayerState<APlayerState>())
    {
        UE_LOG(LogTemp, Log, TEXT("Player Joined: %s"), *PS->GetPlayerName());
    }

    // Optionally update UI or replicated vars
}

void ALobbyGameMode::Logout(AController* Exiting)
{
    Super::Logout(Exiting);

    // Optionally update UI or player list
}

void ALobbyGameMode::TryStartGame()
{
    ALobbyGameState* LobbyGS = GetGameState<ALobbyGameState>();
    if (LobbyGS && LobbyGS->AreAllPlayersReady())
    {
        // Load gameplay map
        //UGameplayStatics::OpenLevel(this, FName("GameMap"), true, "listen");
    }
}