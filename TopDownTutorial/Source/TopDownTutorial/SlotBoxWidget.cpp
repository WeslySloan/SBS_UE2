// Fill out your copyright notice in the Description page of Project Settings.


#include "SlotBoxWidget.h"
#include "SlotWidget.h"
#include "Components/UniformGridPanel.h"

USlotBoxWidget::USlotBoxWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

	ConstructorHelpers::FClassFinder<USlotWidget> SW(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/WBP_Slot.WBP_Slot'"));
	if (SW.Succeeded())
	{
		SlotWidgetClass = SW.Class;

	}
}

void USlotBoxWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UE_LOG(LogTemp, Log, TEXT("NativeConstruct"));

	const int X_COUNT = 4;
	const int Y_COUNT = 8;

	for (int y = 0; y < Y_COUNT; y++)
	{
		for (int x = 0; x < X_COUNT; x++)
		{
			UE_LOG(LogTemp, Log, TEXT("X : %d, Y : %d"), x, y);
			USlotWidget* SlotWidget = CreateWidget<USlotWidget>(GetOwningPlayer(), SlotWidgetClass);
			GridPanel->AddChildToUniformGrid(SlotWidget, x, y);

		}

	}
}
