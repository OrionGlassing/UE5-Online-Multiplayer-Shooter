// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "BlasterPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class BLASTER_API ABlasterPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Replication notifies
	virtual void OnRep_Score() override;
	UFUNCTION()
	virtual void OnRep_Defeats();
	UFUNCTION()
	virtual void OnRep_VictimName();
	UFUNCTION()
	virtual void OnRep_AttackerName();
	
	void AddToScore(float ScoreAmount);
	void AddToDefeats(int32 DefeatsAmount);
	void SetVictimName(FString Name);
	void SetAttackerName(FString Name);
	


private:
	UPROPERTY()
	class ABlasterCharacter* Character;
	UPROPERTY()
	class ABlasterPlayerController* Controller;
	UPROPERTY()
	class ABlasterGameMode* GameMode;

	UPROPERTY(ReplicatedUsing = OnRep_Defeats)
	int32 Defeats;

	UPROPERTY(ReplicatedUsing = OnRep_VictimName)
	FString VictimName;

	UPROPERTY(ReplicatedUsing = OnRep_AttackerName)
	FString AttackerName;
	
	FTimerHandle VictimTimer;
	FTimerHandle KillerTimer;

	UPROPERTY(EditDefaultsOnly)
	float TextDelay = 3.f;

	UFUNCTION()
	void KillerTextTimerFinished();
	UFUNCTION()
	void ElimTextTimerFinished();
	
public:
	FORCEINLINE int32 GetDefeats() const { return Defeats; }
};


