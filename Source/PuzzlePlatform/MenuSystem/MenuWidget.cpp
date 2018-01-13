// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuWidget.h"

void UMenuWidget::Setup()
{
    UE_LOG(LogTemp, Warning, TEXT("Opening Menu System"));
    this->AddToViewport();

    UWorld *World = GetWorld();
    if (!ensure(World != nullptr))
        return;

    APlayerController *APlayerController = World->GetFirstPlayerController();

    if (!ensure(APlayerController != nullptr))
        return;

    FInputModeUIOnly InputMode;
    InputMode.SetWidgetToFocus(this->TakeWidget());
    InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

    APlayerController->SetInputMode(InputMode);
    APlayerController->bShowMouseCursor = true;
}

void UMenuWidget::OnLevelRemovedFromWorld(ULevel *InLevel, UWorld *InWorld)
{
    Teardown();
}

void UMenuWidget::Teardown() 
{
    UE_LOG(LogTemp, Warning, TEXT("Removing Menu System"));

    this->RemoveFromViewport();

    UWorld *World = GetWorld();
    if (!ensure(World != nullptr))
        return;

    APlayerController *APlayerController = World->GetFirstPlayerController();
    if (!ensure(APlayerController != nullptr))
        return;

    FInputModeGameOnly InputMode;
    APlayerController->SetInputMode(InputMode);
    APlayerController->bShowMouseCursor = false;
}

void UMenuWidget::SetMenuInterface(IMenuInterface *MenuInterfacePtr)
{
    MenuInterface = MenuInterfacePtr;
}