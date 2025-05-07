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
private:
	const int COLUMN = 8;
	const int ROW = 4;
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
	TArray<TObjectPtr<USlotWidget>> SlotWidgets;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUniformGridPanel> GridPanel;
protected:
	void InventoryItemChanged(const FIntPoint& ItemSlotPos);

public:
	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual bool NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
};
