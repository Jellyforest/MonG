// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyboardWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "MonGGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "ScoreWidgetActor.h"
#include "ScoreWidget.h"
#include <UMG/Public/Components/WidgetComponent.h>
#include "KeyBoard.h"

#define PRINTTOScreen(msg) GEngine->AddOnScreenDebugMessage(0, 1, FColor::Blue, msg)

void UKeyboardWidget::NativeConstruct()
{
	buttonArray = {btn_Q, btn_W, btn_E, btn_R, btn_T, btn_Y, btn_U, btn_I, btn_O, btn_P, btn_A, btn_S, btn_D, btn_F, btn_G, btn_H, btn_J, btn_K, btn_L, btn_Z, btn_X, btn_C, btn_V, btn_B, btn_N, btn_M};
	spellArray = { TEXT("Q"), TEXT("W"),TEXT("E"), TEXT("R"), TEXT("T"), TEXT("Y"), TEXT("U"), TEXT("I"), TEXT("O"), TEXT("P"), TEXT("A"), TEXT("S"), TEXT("D"), TEXT("F"), TEXT("G"), TEXT("H"), TEXT("J"), TEXT("K"), TEXT("L"), TEXT("Z"), TEXT("X"), TEXT("C"), TEXT("V"), TEXT("B"), TEXT("N"), TEXT("M") };
	////for (int i = 0; i < buttonArray.Num(); i++)
	//{
	/////	if (spellArray.IsValidIndex(i))
	///	{
	///		buttonArray[i]->SetText(FText::FromString((spellArray)));
	///	}
	//}
	//editText_id->SetText(FText::FromString(""));
	btn_Q->OnClicked.AddDynamic(this, &UKeyboardWidget::Click_Q);
	btn_W->OnClicked.AddDynamic(this, &UKeyboardWidget::Click_W);
	btn_E->OnClicked.AddDynamic(this, &UKeyboardWidget::Click_E);
	btn_R->OnClicked.AddDynamic(this, &UKeyboardWidget::Click_R);
	btn_T->OnClicked.AddDynamic(this, &UKeyboardWidget::Click_T);
	btn_Y->OnClicked.AddDynamic(this, &UKeyboardWidget::Click_Y);
	btn_U->OnClicked.AddDynamic(this, &UKeyboardWidget::Click_U);
	btn_I->OnClicked.AddDynamic(this, &UKeyboardWidget::Click_I);
	btn_O->OnClicked.AddDynamic(this, &UKeyboardWidget::Click_O);
	btn_P->OnClicked.AddDynamic(this, &UKeyboardWidget::Click_P);
	btn_A->OnClicked.AddDynamic(this, &UKeyboardWidget::Click_A);
	btn_S->OnClicked.AddDynamic(this, &UKeyboardWidget::Click_S);
	btn_D->OnClicked.AddDynamic(this, &UKeyboardWidget::Click_D);
	btn_F->OnClicked.AddDynamic(this, &UKeyboardWidget::Click_F);
	btn_G->OnClicked.AddDynamic(this, &UKeyboardWidget::Click_G);
	btn_H->OnClicked.AddDynamic(this, &UKeyboardWidget::Click_H);
	btn_J->OnClicked.AddDynamic(this, &UKeyboardWidget::Click_J);
	btn_K->OnClicked.AddDynamic(this, &UKeyboardWidget::Click_K);
	btn_L->OnClicked.AddDynamic(this, &UKeyboardWidget::Click_L);
	btn_Z->OnClicked.AddDynamic(this, &UKeyboardWidget::Click_Z);
	btn_X->OnClicked.AddDynamic(this, &UKeyboardWidget::Click_X);
	btn_C->OnClicked.AddDynamic(this, &UKeyboardWidget::Click_C);
	btn_V->OnClicked.AddDynamic(this, &UKeyboardWidget::Click_V);
	btn_B->OnClicked.AddDynamic(this, &UKeyboardWidget::Click_B);
	btn_N->OnClicked.AddDynamic(this, &UKeyboardWidget::Click_N);
	btn_M->OnClicked.AddDynamic(this, &UKeyboardWidget::Click_M);
	btn_Enter->OnClicked.AddDynamic(this, &UKeyboardWidget::Enter);
	//idTextArray.SetNum(4); 
}

void UKeyboardWidget::Click_Q()
{
	UE_LOG(LogTemp, Warning, TEXT("click q"));
	idTextArray.Add(TEXT("Q"));

	//for (int32 i = 0; i != idTextArray.Num(); ++i)
	//{
	//	editText_id->SetText(FText::FromString(""));
		//UE_LOG(LogTemp, Warning, TEXT("Info= %s"), *idTextArray[i]);
		//resultArray += idTextArray[i];
	//}
		//resultArray = editText_id;
			

	//editText_id->SetText(FText::FromString(idTextArray[4]));

}

void UKeyboardWidget::Click_W()
{
	UE_LOG(LogTemp, Warning, TEXT("click W"));
	idTextArray.Add(TEXT("W"));
	
	/*
	for (int32 i = 0; i != idTextArray.Num(); ++i)
	{
		UE_LOG(LogTemp, Warning, TEXT("Info= %s"), *idTextArray[i]);
		resultArray += idTextArray[i];
		//editText_id->SetText(FText::FromString(""));
	}
	for (int32 i = 0; i != idTextArray.Num(); ++i)
	{
		idTextArray[i];
		editText_id->SetText(FText::FromString(FString::ToHexBlob(idTextArray));

	}
	*/
}

void UKeyboardWidget::Click_E()
{
	UE_LOG(LogTemp, Warning, TEXT("click E"));
	idTextArray.Add(TEXT("E"));
	
}

void UKeyboardWidget::Click_R()
{
	UE_LOG(LogTemp, Warning, TEXT("click R"));

	idTextArray.Add(TEXT("R"));
}

void UKeyboardWidget::Click_T()
{
	UE_LOG(LogTemp, Warning, TEXT("click T"));

	idTextArray.Add(TEXT("T"));
}

void UKeyboardWidget::Click_Y()
{
	UE_LOG(LogTemp, Warning, TEXT("click Y"));

	idTextArray.Add(TEXT("Y"));
}

void UKeyboardWidget::Click_U()
{
	UE_LOG(LogTemp, Warning, TEXT("click U"));

	idTextArray.Add(TEXT("U"));
}

void UKeyboardWidget::Click_I()
{
	UE_LOG(LogTemp, Warning, TEXT("click I"));

	idTextArray.Add(TEXT("I"));
}

void UKeyboardWidget::Click_O()
{
	UE_LOG(LogTemp, Warning, TEXT("click o"));

	idTextArray.Add(TEXT("O"));
}

void UKeyboardWidget::Click_P()
{
	UE_LOG(LogTemp, Warning, TEXT("click p"));

	idTextArray.Add(TEXT("P"));

}

void UKeyboardWidget::Click_A()
{
	idTextArray.Add(TEXT("A"));
}

void UKeyboardWidget::Click_S()
{
	idTextArray.Add(TEXT("S"));
}

void UKeyboardWidget::Click_D()
{
	idTextArray.Add(TEXT("D"));
}

void UKeyboardWidget::Click_F()
{
	idTextArray.Add(TEXT("F"));
}

void UKeyboardWidget::Click_G()
{
	idTextArray.Add(TEXT("G"));
}

void UKeyboardWidget::Click_H()
{
	idTextArray.Add(TEXT("H"));
}

void UKeyboardWidget::Click_J()
{
	idTextArray.Add(TEXT("J"));
}

void UKeyboardWidget::Click_K()
{
	idTextArray.Add(TEXT("K"));
}

void UKeyboardWidget::Click_L()
{
	idTextArray.Add(TEXT("L"));
}

void UKeyboardWidget::Click_Z()
{
	idTextArray.Add(TEXT("Z"));
}

void UKeyboardWidget::Click_X()
{
	idTextArray.Add(TEXT("X"));
}

void UKeyboardWidget::Click_C()
{
	idTextArray.Add(TEXT("C"));
}

void UKeyboardWidget::Click_V()
{
	idTextArray.Add(TEXT("V"));
}

void UKeyboardWidget::Click_B()
{
	idTextArray.Add(TEXT("B"));
}

void UKeyboardWidget::Click_N()
{
	idTextArray.Add(TEXT("N"));
}

void UKeyboardWidget::Click_M()
{
	idTextArray.Add(TEXT("M"));
}

void UKeyboardWidget::Enter()
{
	for (int32 i = 0; i != idTextArray.Num(); ++i)
	{
		editText_id->SetText(FText::FromString(""));
		resultArray += idTextArray[i];
		editText_id->SetText(FText::FromString(resultArray));
		//UE_LOG(LogTemp, Warning, TEXT("%s"), SetText(FText::FromString(resultArray)));
		//PRINTTOScreen((TEXT("%s"), resultArray));

	}
	AMonGGameModeBase* monGgm = Cast<AMonGGameModeBase>(UGameplayStatics::GetGameMode(this));
	scoreWidgetActor = Cast<AScoreWidgetActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AScoreWidgetActor::StaticClass()));
	scoreWidget = Cast<UScoreWidget>(scoreWidgetActor->scoreWidgetComp->GetWidget());
	keyboard = Cast<AKeyBoard>(UGameplayStatics::GetActorOfClass(GetWorld(), AKeyBoard::StaticClass()));

	scoreWidget->PrintCurrentScore();
	monGgm->PlusRanking(scoreID);
	keyboard->keyboardWidgetComp->SetVisibility(false);
}

