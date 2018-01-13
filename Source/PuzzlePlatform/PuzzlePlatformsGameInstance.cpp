// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformsGameInstance.h"

#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

#include "MenuSystem/MainMenu.h"
#include "MenuSystem/MenuWidget.h"
#include "PlatformTrigger.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer &ObjectInitializer)
{
    ConstructorHelpers::FClassFinder<UUserWidget> MenuSystemBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));

    if (!ensure(MenuSystemBPClass.Class != nullptr))
        return;

    MenuClass = MenuSystemBPClass.Class;

    ConstructorHelpers::FClassFinder<UUserWidget> GameMenuSystemBPClass(TEXT("/Game/MenuSystem/WBP_GameMenu"));

    if (!ensure(GameMenuSystemBPClass.Class != nullptr))
        return;

    GameMenuClass = GameMenuSystemBPClass.Class;
}

void UPuzzlePlatformsGameInstance::Init() 
{
    UE_LOG(LogTemp, Warning, TEXT("Found Class %s"), *MenuClass->GetName());
}

void UPuzzlePlatformsGameInstance::Host() 
{
    UEngine* Engine = GetEngine();

    if(!ensure(Engine != nullptr)) return;

    Engine->AddOnScreenDebugMessage(0,2,FColor::Green,TEXT("Hosting"));

    UWorld* World = GetWorld();
    if(!ensure(World != nullptr)) return;

    World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UPuzzlePlatformsGameInstance::Join(const FString& Address)
{
    UEngine *Engine = GetEngine();

    if (!ensure(Engine != nullptr))
        return;

    Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, FString::Printf(TEXT("Joining %s"),*Address));

    APlayerController* APlayerController = GetFirstLocalPlayerController();

    if (!ensure(APlayerController != nullptr))
        return;

    APlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}

void UPuzzlePlatformsGameInstance::LoadMenu() 
{
    if(!ensure(MenuClass != nullptr)) return;

    UMenuWidget *Menu = CreateWidget<UMenuWidget>(this, MenuClass);
    if(!ensure(Menu != nullptr)) return;
    
    Menu->Setup();
   
    Menu->SetMenuInterface(this);
}

void UPuzzlePlatformsGameInstance::LoadGameMenu()
{
    if (!ensure(GameMenuClass != nullptr))
        return;

    UMenuWidget *Menu = CreateWidget<UMenuWidget>(this, GameMenuClass);
    if (!ensure(Menu != nullptr))
        return;

    Menu->Setup();

    Menu->SetMenuInterface(this);
}