// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StartWidget.generated.h"

/**
 * 
 */
UCLASS()
class MONG_API UStartWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	virtual void NativeConstruct() override;

public:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	//class UWidgetSwitcher* widgetSwitcher;

};
