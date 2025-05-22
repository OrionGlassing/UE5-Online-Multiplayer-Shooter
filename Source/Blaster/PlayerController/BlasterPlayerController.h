// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Blaster/Weapon/WeaponTypes.h"
#include "BlasterPlayerController.generated.h"

UCLASS()
class BLASTER_API ABlasterPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	void SetHUDHealth(float Health, float MaxHealth);
	void SetHUDScore(float Score);
	void SetHUDDefeats(int32 Defeats);
	void SetHUDWeaponAmmo(int32 Ammo, int32 MagSize);
	void SetHUDCarriedAmmo(int32 CarriedAmmo);
	void SetHUDKillerName(FString KillerName);
	void SetHUDElimName(FString ElimName);
	void ShowKillerName();
	void HideKillerName();
	void ShowElimName();
	void HideElimName();
	void SetHUDWeapon(EWeaponType WeaponType);
	void ShowHUDWeapon();
	void HideHUDWeapon();
	void SetHUDMatchCountdown(float CountdownTime);
	void SetHUDAnnouncementCountdown(float CountdownTime);
	void HandleShowSettingsMenu();
	void HandleHideSettingsMenu();
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;

	virtual float GetServerTime(); //Synced with server world clock
	virtual void ReceivedPlayer() override; // Earliest possible point to get time from server

	void OnMatchStateSet(FName State);
	void HandleMatchHasStarted();
	void HandleCooldown();

	bool SettingsMenuVisibility;
	
protected:
	virtual void BeginPlay() override;
	void SetHUDTime();
	void PollInit();
	
	void UpdateAimSensitivity();

	//
	// Sync Time between Client and Server
	//
	
	// Requests the current server time, passing in the clients time when request was sent
	UFUNCTION(Server, Reliable)
	void ServerRequestServerTime(float TimeOfClientRequest);

	// Reports the current server time to the client, 
	UFUNCTION(Client, Reliable)
	void ClientReportServerTime(float TimeOfClientRequest, float TimeServerReceivedClientRequest);

	// Difference between Client and Server Time
	float ClientServerDelta = 0.f;

	UPROPERTY(EditAnywhere, Category = Time)
	float TimeSyncRate = 5.f;

	float TimeSyncRunningTime = 0.f;
	void CheckTimeSync(float DeltaTime);

	UFUNCTION(Server, Reliable)
	void ServerCheckMatchState();

	UFUNCTION(Client, Reliable)
	void ClientJoinMidGame(FName StateOfMatch, float Warmup, float Match, float Cooldown, float StartingTime);
	
private:
	UPROPERTY()
	class ABlasterHUD* BlasterHUD;

	UPROPERTY()
	class ABlasterGameMode* BlasterGameMode;

	bool ShowingKillerText;
	bool ShowingElimText;

	float LevelStartingTime = 0.f;
	float MatchTime = 0.f;
	float WarmupTime = 0.f;
	float CooldownTime = 0.f;
	uint32 CountdownInt = 0;

	UPROPERTY(ReplicatedUsing = OnRep_MatchState)
	FName MatchState;

	UFUNCTION()
	void OnRep_MatchState();

	UPROPERTY()
	class UCharacterOverlay* CharacterOverlay;
	
	bool bInitializeCharacterOverlay = false;

	float HUDHealth;
	float HUDMaxHealth;
	float HUDScore;
	int32 HUDDefeats;

public:
	FORCEINLINE bool SettingsMenuIsVisible() const { return SettingsMenuVisibility; }
};
