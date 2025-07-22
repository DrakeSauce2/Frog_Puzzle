// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class UButton;
class UImage;
class UTexture2D;
/**
 * 
 */
UCLASS()
class UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

protected:
	/** Buttons */
	UPROPERTY(meta = (BindWidget))
	UButton* StartButton;

	UPROPERTY(meta = (BindWidget))
	UButton* InviteFriendsButton;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;

	UPROPERTY(meta = (BindWidget))
	UButton* SettingsButton;

	/** Steam avatars */
	UPROPERTY(meta = (BindWidget))
	UImage* Owner_Profile;

	UPROPERTY(meta = (BindWidget))
	UImage* Friend_Profile;

	/** Button handlers */
	UFUNCTION()
	void OnStartClicked();

	UFUNCTION()
	void OnInviteClicked();

	UFUNCTION()
	void OnQuitClicked();

	UFUNCTION()
	void OnSettingsClicked();

	class APlayerState* GetOwningPlayerState() const;

	/** Avatar population helper */
	void UpdateProfileIcons();

	UTexture2D* GetSteamAvatar();
	UTexture2D* GetFriendSteamAvatar();

	uint64 GetSteamIDFromPlayerState(APlayerState* PS) const;
	UTexture2D* GetSteamAvatarFromSteamID(uint64 SteamID);
};
