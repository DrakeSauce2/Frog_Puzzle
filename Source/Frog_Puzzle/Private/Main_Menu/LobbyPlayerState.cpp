// Fill out your copyright notice in the Description page of Project Settings.


#include "Main_Menu/LobbyPlayerState.h"
#include "Net/UnrealNetwork.h"

ALobbyPlayerState::ALobbyPlayerState()
{
	bIsReady = false;
	bReplicates = true;
}

void ALobbyPlayerState::OnRep_IsReady()
{
	// UI update logic on clients (if needed)
}

void ALobbyPlayerState::Server_SetReady_Implementation(bool bNewReady)
{
	bIsReady = bNewReady;
	OnRep_IsReady(); // Optional for server-side UI
}

void ALobbyPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALobbyPlayerState, bIsReady);
}
