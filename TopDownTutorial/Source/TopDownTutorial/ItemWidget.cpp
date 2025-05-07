// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "ItemDragWidget.h"
#include "ItemDragDropOperation.h"

UItemWidget::UItemWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UItemDragWidget> IDW(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/WBP_ItemDrag.WBP_ItemDrag_C'"));
	if (IDW.Succeeded())
	{
		ItemDragWidgetClass = IDW.Class;
	}
}

void UItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Text_Count->SetText(FText::GetEmpty());
}

void UItemWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	Image_Hover->SetRenderOpacity(1.f);

}

void UItemWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	Image_Hover->SetRenderOpacity(0.f);
}

FReply UItemWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		Reply.DetectDrag(TakeWidget(), EKeys::LeftMouseButton);

	}

	return Reply;
}

void UItemWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	UItemDragWidget* ItemDragWidget = CreateWidget<UItemDragWidget>(GetWorld(), ItemDragWidgetClass);

	UItemDragDropOperation* DragDrop = NewObject<UItemDragDropOperation>();
	DragDrop->DefaultDragVisual = ItemDragWidget;
	DragDrop->Pivot = EDragPivot::MouseDown;
	//DragDrop->FromSlotPos =  ???? 


	OutOperation = DragDrop;



}

void UItemWidget::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);
	UE_LOG(LogTemp, Log, TEXT("NativeOnDragCancelled"));
}
