// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OverHeadWidget.generated.h"

/**
 * 
 */
UCLASS()
class BLASTER_API UOverHeadWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* DisplayText;

	void SetDisplayText(FString TextToDisplay);

	UFUNCTION(BlueprintCallable)
	void ShowPlayerName(APawn* InPawn);

protected:
	virtual void NativeDestruct() override;

private:
	UPROPERTY(EditAnywhere, Category="Overhead Widget Properties", meta=(AllowPrivateAccess=true, Units="Seconds"))
	float GetPlayerNameTimeout = 30.f;
	
	UPROPERTY(EditAnywhere, Category="Overhead Widget Properties", meta=(AllowPrivateAccess=true, Units="Seconds"))
	float GetPlayerNameInterval = 0.1f;
	
	float TotalTime = -0.1f;
	
};
