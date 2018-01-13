// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"

bool UMainMenu::Initialize()
{
    bool Success = Super::Initialize();

    if(!Success) return false;

    if (!ensure(HostButton != nullptr))
        return false;

    HostButton -> OnClicked.AddDynamic(this, &UMainMenu::HostServer);

    if (!ensure(JoinButton != nullptr))
        return false;

    JoinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);

    if (!ensure(BackButton != nullptr))
        return false;

    BackButton->OnClicked.AddDynamic(this, &UMainMenu::BackToMainMenu);

    if (!ensure(JoinServerButton != nullptr))
        return false;

    JoinServerButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);

    return true;
}



void UMainMenu::HostServer()
{
    if(MenuInterface != nullptr) {
        UE_LOG(LogTemp, Display, TEXT("Hosting Server"));
        MenuInterface->Host();
    }
}

void UMainMenu::OpenJoinMenu() {
    if(!ensure(MenuSwitcher != nullptr)) return;
    if(!ensure(JoinMenu != nullptr)) return;

    MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenu::BackToMainMenu() {
    if (!ensure(MenuSwitcher != nullptr))
        return;
    if (!ensure(MainMenu != nullptr))
        return;

    MenuSwitcher->SetActiveWidget(MainMenu);
}

void UMainMenu::JoinServer()
{
    if(!ensure(IPAddressTextBox != nullptr)) return;

    if (MenuInterface != nullptr)
    {
        const FString IP = IPAddressTextBox -> GetText().ToString();
        MenuInterface->Join(IP);
    }
}
