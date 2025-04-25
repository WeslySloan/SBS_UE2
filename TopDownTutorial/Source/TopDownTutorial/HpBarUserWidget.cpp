// Fill out your copyright notice in the Description page of Project Settings.


#include "HpBarUserWidget.h"
#include "CharacterInfo.h"
#include "Components/ProgressBar.h"

void UHpBarUserWidget::BindHp(UCharacterInfo* Info)
{
	CharacterInfo = Info;
	CharacterInfo->OnHpChanaged.AddUObject(this, &UHpBarUserWidget::UpdateHp);

	UpdateHp();

}

void UHpBarUserWidget::UpdateHp()
{
	PB_Bar->SetPercent(CharacterInfo->GetHpRatio());
}
