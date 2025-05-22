// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Slider.h"
#include "SettingsMenu.generated.h"

/**
 * 
 */
UCLASS()
class BLASTER_API USettingsMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget))
	class USlider* AimSensitivitySlider;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* AimSensitivityValue;

	FORCEINLINE float GetAimSensitivity() const { return AimSensitivitySlider->GetNormalizedValue(); }
	
};
