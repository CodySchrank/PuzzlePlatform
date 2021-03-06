// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"

#include "PuzzlePlatformsGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORM_API UPuzzlePlatformsGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()

	public:
	  UPuzzlePlatformsGameInstance(const FObjectInitializer &ObjectInitializer);

	  virtual void Init();

	  UFUNCTION(exec)
	  void Host();
	  
	  UFUNCTION(exec)
	  void Join(const FString& Address);

	  UFUNCTION(BlueprintCallable)
	  void LoadMenu();

	  UFUNCTION(BlueprintCallable)
	  void LoadGameMenu();

	private:
	TSubclassOf<class UUserWidget> MenuClass;
	TSubclassOf<class UUserWidget> GameMenuClass;

	class UMainMenu *Menu;
};
