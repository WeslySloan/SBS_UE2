// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SlotBoxWidget.generated.h"

/**
 * 
 */
class UItemWidget;
class USlotWidget;
class UUniformGridPanel;


UCLASS()
class TOPDOWNTUTORIAL_API USlotBoxWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	USlotBoxWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
protected:
	virtual void NativeConstruct() override;
public:
	UPROPERTY()
	TSubclassOf<USlotWidget> SlotWidgetClass;

	UPROPERTY()
	TSubclassOf<UItemWidget> ItemWidgetClass;
	
	UPROPERTY()
	TArray<USlotWidget*> SlotWidgets;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUniformGridPanel> GridPanel;
};
