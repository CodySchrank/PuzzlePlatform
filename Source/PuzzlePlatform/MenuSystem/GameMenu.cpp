// Fill out your copyright notice in the Description page of Project Settings.

#include "GameMenu.h"

#include "Components/Button.h"

bool UGameMenu::Initialize() {
        bool Success = Super::Initialize();

        if (!Success)
            return false;

        if (!ensure(CancelButton != nullptr))
            return false;

        CancelButton->OnClicked.AddDynamic(this, &UGameMenu::CancelButtonPressed);
}

void UGameMenu::CancelButtonPressed()
{
    Teardown();
}