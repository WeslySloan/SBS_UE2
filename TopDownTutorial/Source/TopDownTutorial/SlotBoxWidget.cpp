// Fill out your copyright notice in the Description page of Project Settings.


#include "SlotBoxWidget.h"
#include "SlotWidget.h"
#include "ItemWidget.h"
#include "Components/UniformGridPanel.h"
#include "Blueprint/DragDropOperation.h"

USlotBoxWidget::USlotBoxWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

	ConstructorHelpers::FClassFinder<USlotWidget> SW(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/WBP_Slot.WBP_Slot_C'"));
	if (SW.Succeeded())
	{
		SlotWidgetClass = SW.Class;

	}

	ConstructorHelpers::FClassFinder<UItemWidget> IW(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/WBP_Item.WBP_Item_C'"));
	if (IW.Succeeded())
	{
		ItemWidgetClass = IW.Class;
		UE_LOG(LogTemp, Log, TEXT("Item Widget"));

	}
}

void USlotBoxWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SlotWidgets.SetNum(COLUMN * ROW);

	for (int x = 0; x < ROW; x++)
	{
		for (int y = 0; y < COLUMN; y++)
		{
			USlotWidget* SlotWidget = CreateWidget<USlotWidget>(GetWorld(), SlotWidgetClass);

			int32 index = x * COLUMN + y;
			SlotWidgets[index] = SlotWidget;
			GridPanel->AddChildToUniformGrid(SlotWidget, y, x);

		}

	}

	UItemWidget* ItemWidget = CreateWidget<UItemWidget>(GetWorld(), ItemWidgetClass);
	GridPanel->AddChildToUniformGrid(ItemWidget, 0, 0);

}

void USlotBoxWidget::InventoryItemChanged(const FIntPoint& ItemSlotPos)
{
	int32 slotIndex = ItemSlotPos.Y * ROW + ItemSlotPos.X;

	UE_LOG(LogTemp, Log, TEXT("Index : %d"), slotIndex);
}

void USlotBoxWidget::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragLeave(InDragDropEvent, InOperation);
	UE_LOG(LogTemp, Log, TEXT("NativeOnDragLeave"));
}

bool USlotBoxWidget::NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragOver(InGeometry, InDragDropEvent, InOperation);
	//UE_LOG(LogTemp, Log, TEXT("NativeOnDragOver"));

	//InventoryItemChanged();
	return false;
}

bool USlotBoxWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	UE_LOG(LogTemp, Log, TEXT("NativeOnDrop"));
	return false;
}
