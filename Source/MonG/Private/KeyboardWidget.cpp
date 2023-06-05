// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyboardWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/EditableText.h"


void UKeyboardWidget::NativeConstruct()
{
	editText_id->SetText(FText::FromString(""));
	btn_Q->OnClicked.AddDynamic(this, &UKeyboardWidget::Click_Q);

}

void UKeyboardWidget::Click_Q()
{

}
