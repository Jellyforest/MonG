// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyboardButton.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UKeyboardButton::NativeConstruct()
{
	btn_Spell->OnClicked.AddDynamic(this, &UKeyboardButton::Click_btn);

}

void UKeyboardButton::Click_btn()
{
	UE_LOG(LogTemp, Warning, TEXT("keyboardbuton click"));
}
