// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KeyboardWidget.generated.h"

/**
 * 
 */
UCLASS()
class MONG_API UKeyboardWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UEditableText* editText_id;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UButton* btn_Q;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UButton* btn_W;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UButton* btn_E;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UButton* btn_R;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UButton* btn_T;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UButton* btn_Y;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UButton* btn_U;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UButton* btn_I;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UButton* btn_O;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UButton* btn_P;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UButton* btn_A;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UButton* btn_S;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UButton* btn_D;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UButton* btn_F;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UButton* btn_G;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UButton* btn_H;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UButton* btn_J;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UButton* btn_K;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UButton* btn_L;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UButton* btn_Z;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UButton* btn_X;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UButton* btn_C;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UButton* btn_V;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UButton* btn_B;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UButton* btn_N;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UButton* btn_M;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	class UButton* btn_Enter;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	TArray <UButton*> buttonArray;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	TArray<FString> spellArray;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	TArray<FString> idTextArray;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	FString resultArray;


	UFUNCTION(BlueprintCallable)
	void Click_Q();
	UFUNCTION(BlueprintCallable)
	void Click_W();
	UFUNCTION(BlueprintCallable)
	void Click_E();
	UFUNCTION(BlueprintCallable)
	void Click_R();
	UFUNCTION(BlueprintCallable)
	void Click_T();
	UFUNCTION(BlueprintCallable)
	void Click_Y();
	UFUNCTION(BlueprintCallable)
	void Click_U();
	UFUNCTION(BlueprintCallable)
	void Click_I();
	UFUNCTION(BlueprintCallable)
	void Click_O();
	UFUNCTION(BlueprintCallable)
	void Click_P();
	UFUNCTION(BlueprintCallable)
	void Click_A();
	UFUNCTION(BlueprintCallable)
	void Click_S();
	UFUNCTION(BlueprintCallable)
	void Click_D();
	UFUNCTION(BlueprintCallable)
	void Click_F();
	UFUNCTION(BlueprintCallable)
	void Click_G();
	UFUNCTION(BlueprintCallable)
	void Click_H();
	UFUNCTION(BlueprintCallable)
	void Click_J();
	UFUNCTION(BlueprintCallable)
	void Click_K();
	UFUNCTION(BlueprintCallable)
	void Click_L();
	UFUNCTION(BlueprintCallable)
	void Click_Z();
	UFUNCTION(BlueprintCallable)
	void Click_X();
	UFUNCTION(BlueprintCallable)
	void Click_C();
	UFUNCTION(BlueprintCallable)
	void Click_V();
	UFUNCTION(BlueprintCallable)
	void Click_B();
	UFUNCTION(BlueprintCallable)
	void Click_N();
	UFUNCTION(BlueprintCallable)
	void Click_M();
	UFUNCTION(BlueprintCallable)
	void Enter();

};
