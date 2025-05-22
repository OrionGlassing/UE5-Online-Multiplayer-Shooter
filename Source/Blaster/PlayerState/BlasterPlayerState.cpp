// Fill out your copyright notice in the Description page of Project Settings.


#include "BlasterPlayerState.h"
#include "Blaster/Character/BlasterCharacter.h"
#include "Blaster/GameMode/BlasterGameMode.h"
#include "Blaster/PlayerController/BlasterPlayerController.h"
#include "Net/UnrealNetwork.h"
#include "TimerManager.h"

void ABlasterPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABlasterPlayerState, Defeats);
	DOREPLIFETIME(ABlasterPlayerState, VictimName);
	DOREPLIFETIME(ABlasterPlayerState, AttackerName);
}

void ABlasterPlayerState::AddToScore(float ScoreAmount)
{
	SetScore(GetScore() + ScoreAmount);
	Character = Character == nullptr ? Cast<ABlasterCharacter>(GetPawn()) : Character;
	if (Character)
	{
		Controller = Controller == nullptr ? Cast<ABlasterPlayerController>(Character->Controller) : Controller;
		if (Controller)
		{
			Controller->SetHUDScore(GetScore());
		}
	}
}

void ABlasterPlayerState::AddToDefeats(int32 DefeatsAmount)
{
	Defeats += DefeatsAmount;
	Character = Character == nullptr ? Cast<ABlasterCharacter>(GetPawn()) : Character;
	if (Character)
	{
		Controller = Controller == nullptr ? Cast<ABlasterPlayerController>(Character->Controller) : Controller;
		if (Controller)
		{
			Controller->SetHUDDefeats(Defeats);
		}
	}
}

void ABlasterPlayerState::SetVictimName(FString Name)
{
	GameMode = GameMode == nullptr ? Cast<ABlasterGameMode>(GetWorld()->GetAuthGameMode()) : GameMode;
	VictimName = Name;
	
	Character = Character == nullptr ? Cast<ABlasterCharacter>(GetPawn()) : Character;
	if (Character && !VictimName.IsEmpty())
	{
		Controller = Controller == nullptr ? Cast<ABlasterPlayerController>(Character->Controller) : Controller;
		if (Controller)
		{
			Controller->SetHUDElimName(VictimName);
			Controller->ShowElimName();

			FTimerDelegate TimerDelegate;
			TimerDelegate.BindUFunction(this, "ElimTextTimerFinished");
			
			GetWorldTimerManager().SetTimer(
				VictimTimer,
				TimerDelegate,
				TextDelay,
				false
				);
		}
	}
}

void ABlasterPlayerState::SetAttackerName(FString Name)
{
	GameMode = GameMode == nullptr ? Cast<ABlasterGameMode>(GetWorld()->GetAuthGameMode()) : GameMode;
	AttackerName = Name;

	Character = Character == nullptr ? Cast<ABlasterCharacter>(GetPawn()) : Character;
	if (Character && !AttackerName.IsEmpty())
	{
		Controller = Controller == nullptr ? Cast<ABlasterPlayerController>(Character->Controller) : Controller;
		if (Controller)
		{
			Controller->SetHUDKillerName(AttackerName);
			Controller->ShowKillerName();

			FTimerDelegate TimerDelegate;
			TimerDelegate.BindUFunction(this, "KillerTextTimerFinished");
			
			GetWorldTimerManager().SetTimer(
				KillerTimer,
				TimerDelegate,
				TextDelay,
				false
				);
		}
	}
}

void ABlasterPlayerState::KillerTextTimerFinished()
{
	Controller = Controller == nullptr ? Cast<ABlasterPlayerController>(Character->Controller) : Controller;
	if (Controller)
	{
		Controller->HideKillerName();
		AttackerName.Empty();
	}
}

void ABlasterPlayerState::ElimTextTimerFinished()
{
	Controller = Controller == nullptr ? Cast<ABlasterPlayerController>(Character->Controller) : Controller;
	if (Controller)
	{
		Controller->HideElimName();
		VictimName.Empty();
	}
}

void ABlasterPlayerState::OnRep_VictimName()
{
	Character = Character == nullptr ? Cast<ABlasterCharacter>(GetPawn()) : Character;
	if (Character)
	{
		Controller = Controller == nullptr ? Cast<ABlasterPlayerController>(Character->Controller) : Controller;
		if (Controller && !VictimName.IsEmpty())
		{
			Controller->SetHUDElimName(VictimName);
			Controller->ShowElimName();

			FTimerDelegate TimerDelegate;
			TimerDelegate.BindUFunction(this, "ElimTextTimerFinished");
			
			GetWorldTimerManager().SetTimer(
				VictimTimer,
				TimerDelegate,
				TextDelay,
				false
				);
		}
	}
}

void ABlasterPlayerState::OnRep_AttackerName()
{
	Character = Character == nullptr ? Cast<ABlasterCharacter>(GetPawn()) : Character;
	if (Character && !AttackerName.IsEmpty())
	{
		Controller = Controller == nullptr ? Cast<ABlasterPlayerController>(Character->Controller) : Controller;
		if (Controller)
		{
			Controller->SetHUDKillerName(AttackerName);
			Controller->ShowKillerName();

			FTimerDelegate TimerDelegate;
			TimerDelegate.BindUFunction(this, "KillerTextTimerFinished");
			
			GetWorldTimerManager().SetTimer(
				KillerTimer,
				TimerDelegate,
				TextDelay,
				false
				);
		}
	}
}

void ABlasterPlayerState::OnRep_Score()
{
	Super::OnRep_Score();

	Character = Character == nullptr ? Cast<ABlasterCharacter>(GetPawn()) : Character;
	if (Character)
	{
		Controller = Controller == nullptr ? Cast<ABlasterPlayerController>(Character->Controller) : Controller;
		if (Controller)
		{
			Controller->SetHUDScore(GetScore());
		}
	}
}

void ABlasterPlayerState::OnRep_Defeats()
{
	Character = Character == nullptr ? Cast<ABlasterCharacter>(GetPawn()) : Character;
	if (Character)
	{
		Controller = Controller == nullptr ? Cast<ABlasterPlayerController>(Character->Controller) : Controller;
		if (Controller)
		{
			Controller->SetHUDDefeats(Defeats);
		}
	}
}
