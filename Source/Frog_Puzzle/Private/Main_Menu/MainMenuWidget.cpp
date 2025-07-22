// Fill out your copyright notice in the Description page of Project Settings.


#include "Main_Menu/MainMenuWidget.h"

#include "Main_Menu/LobbyGameMode.h"
#include "Main_Menu/LobbyGameState.h"
#include "Main_Menu/LobbyPlayerState.h"

#include "AdvancedSteamFriendsLibrary.h"
#include "AdvancedFriendsLibrary.h"
#include "BlueprintDataDefinitions.h"

#include "Components/Button.h"
#include "Components/Image.h"

#include "Engine/Texture2D.h"

#include "GameFramework/PlayerState.h"

#include "Interfaces/OnlineExternalUIInterface.h"

#include "Kismet/GameplayStatics.h"

#include "OnlineSubsystem.h"                      

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (StartButton) StartButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnStartClicked);
	if (InviteFriendsButton) InviteFriendsButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnInviteClicked);
	if (QuitButton) QuitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnQuitClicked);
	if (SettingsButton) SettingsButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnSettingsClicked);

	UpdateProfileIcons();

	if (ALobbyGameState* GS = Cast<ALobbyGameState>(UGameplayStatics::GetGameState(this)))
	{
		GS->OnLobbyPlayersChanged.AddDynamic(this, &UMainMenuWidget::UpdateProfileIcons);
	}
}

void UMainMenuWidget::OnStartClicked()
{
	APlayerController* PC = GetOwningPlayer();
	if (PC && PC->HasAuthority())
	{
		ALobbyGameMode* GM = Cast<ALobbyGameMode>(UGameplayStatics::GetGameMode(this));
		if (GM)
		{
			GM->TryStartGame();
		}
	}
}

void UMainMenuWidget::OnInviteClicked()
{
	// Opens Steam overlay invite dialog
	if (IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get())
	{
		IOnlineExternalUIPtr ExternalUI = Subsystem->GetExternalUIInterface();
		if (ExternalUI.IsValid())
		{
			ExternalUI->ShowInviteUI(0);
		}
	}
}

void UMainMenuWidget::OnQuitClicked()
{
	UWorld* World = GetWorld();
	APlayerController* PC = UGameplayStatics::GetPlayerController(World, 0);
	if (PC)
	{
		PC->ConsoleCommand("quit");
	}
}

void UMainMenuWidget::OnSettingsClicked()
{
	// Placeholder — swap widget, open subpanel, etc.
	UE_LOG(LogTemp, Warning, TEXT("Settings button clicked"));
}

APlayerState* UMainMenuWidget::GetOwningPlayerState() const
{
	if (APlayerController* PC = GetOwningPlayer())
	{
		return PC->PlayerState;
	}

	return nullptr;
}

void UMainMenuWidget::UpdateProfileIcons()
{
	/*
	UTexture2D* Avatar = GetSteamAvatar();
	if (Owner_Profile && Avatar)
	{
		Owner_Profile->SetBrushFromTexture(Avatar);
	}

	UTexture2D* FriendAvatar = GetFriendSteamAvatar();
	if (Friend_Profile && FriendAvatar)
	{
		Friend_Profile->SetBrushFromTexture(FriendAvatar);
	}
	*/
	// Local avatar
	APlayerState* PS = GetOwningPlayerState();
	if (PS && Owner_Profile)
	{
		uint64 LocalSteamID = GetSteamIDFromPlayerState(PS);
		if (LocalSteamID != 0)
		{
			UTexture2D* Avatar = GetSteamAvatarFromSteamID(LocalSteamID);
			if (Avatar)
			{
				Owner_Profile->SetBrushFromTexture(Avatar);
			}
		}
	}

	// Friend avatar
	AGameStateBase* GameState = UGameplayStatics::GetGameState(this);
	if (GameState && Friend_Profile)
	{
		for (APlayerState* OtherPS : GameState->PlayerArray)
		{
			if (OtherPS == PS) continue;

			uint64 FriendSteamID = GetSteamIDFromPlayerState(OtherPS);
			if (FriendSteamID != 0)
			{
				UTexture2D* FriendAvatar = GetSteamAvatarFromSteamID(FriendSteamID);
				if (FriendAvatar)
				{
					Friend_Profile->SetBrushFromTexture(FriendAvatar);
					break;
				}
			}
		}
	}
}

UTexture2D* UMainMenuWidget::GetSteamAvatar()
{
	/*
	APlayerState* PS = GetOwningPlayerState();
	if (!PS) return nullptr;

	FBPUniqueNetId NetID;
	NetID.SetUniqueNetId(PS->GetUniqueId().GetUniqueNetId());

	EBlueprintAsyncResultSwitch Result;
	UTexture2D* Avatar = UAdvancedSteamFriendsLibrary::GetSteamFriendAvatar(NetID, Result, SteamAvatarSize::SteamAvatar_Large);

	if (Result != EBlueprintAsyncResultSwitch::OnSuccess)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to get avatar from PlayerState"));
		return nullptr;
	}

	return Avatar;
	*/
	return nullptr;
}


UTexture2D* UMainMenuWidget::GetFriendSteamAvatar()
{
	/*
	AGameStateBase* GameState = UGameplayStatics::GetGameState(this);
	if (!GameState) return nullptr;

	for (APlayerState* PS : GameState->PlayerArray)
	{
		// Skip yourself
		if (PS == GetOwningPlayerState()) continue;

		FBPUniqueNetId FriendNetId;
		FriendNetId.SetUniqueNetId(PS->GetUniqueId().GetUniqueNetId());

		EBlueprintAsyncResultSwitch Result;
		return UAdvancedSteamFriendsLibrary::GetSteamFriendAvatar(FriendNetId, Result, SteamAvatarSize::SteamAvatar_Large);
	}

	return nullptr;
	*/
	return nullptr;
}

uint64 UMainMenuWidget::GetSteamIDFromPlayerState(APlayerState* PS) const
{
	if (!PS) return 0;

	const TSharedPtr<const FUniqueNetId> NetId = PS->GetUniqueId().GetUniqueNetId();
	if (!NetId.IsValid() || !NetId->IsValid())
	{
		return 0;
	}

	// Convert NetId string to uint64
	FString NetIdStr = NetId->ToString();
	return FCString::Strtoui64(*NetIdStr, nullptr, 10);
}

UTexture2D* UMainMenuWidget::GetSteamAvatarFromSteamID(uint64 SteamID)
{
	if (!SteamAPI_Init())
	{
		UE_LOG(LogTemp, Error, TEXT("Steam API not initialized"));
		return nullptr;
	}

	CSteamID TargetSteamID(SteamID);
	int AvatarID = SteamFriends()->GetLargeFriendAvatar(TargetSteamID);

	if (AvatarID == -1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to get avatar ID from Steam"));
		return nullptr;
	}

	uint32 Width = 0, Height = 0;
	if (!SteamUtils()->GetImageSize(AvatarID, &Width, &Height) || Width == 0 || Height == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid avatar image size"));
		return nullptr;
	}

	TArray<uint8> RawData;
	RawData.SetNumUninitialized(Width * Height * 4); // RGBA

	if (!SteamUtils()->GetImageRGBA(AvatarID, RawData.GetData(), RawData.Num()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to get avatar RGBA data"));
		return nullptr;
	}

	UTexture2D* AvatarTexture = UTexture2D::CreateTransient(Width, Height, PF_R8G8B8A8);
	if (!AvatarTexture) return nullptr;

	void* TextureData = AvatarTexture->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
	FMemory::Memcpy(TextureData, RawData.GetData(), RawData.Num());
	AvatarTexture->GetPlatformData()->Mips[0].BulkData.Unlock();

	AvatarTexture->UpdateResource();

	return AvatarTexture;
}
