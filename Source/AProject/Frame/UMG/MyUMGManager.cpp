// Fill out your copyright notice in the Description page of Project Settings.

#include "MyUMGManager.h"
#include "MyManagerDef.h"
#include "Kismet/GameplayStatics.h"
#include "UserWidget.h"
//#include "MyBlueprintFuncLibrary.h"

UMyUMGManager::UMyUMGManager()
{
	My_LOGCALLF(Log_Base, Log);

	ManagerType = EManagerType::Mgr_UMG;




	
	
	
}

void UMyUMGManager::FinishDestroy()
{
	My_LOGCALLF(Log_Base, Log);
	Super::FinishDestroy();
}

void UMyUMGManager::ManagerInit()
{
	My_LOGCALLF(Log_Frame, Log);
	Super::ManagerInit();

	CreateUMG();
}

void UMyUMGManager::ManagerClear()
{
	My_LOGCALLF(Log_Frame, Log);
	Super::ManagerClear();
	
}

void UMyUMGManager::ManagerStandBy()
{
	My_LOGCALLF(Log_Frame, Log);
	Super::ManagerStandBy();
}

void UMyUMGManager::ManagerBegin()
{
	My_LOGCALLF(Log_Frame, Log);
	Super::ManagerBegin();
}

void UMyUMGManager::ManagerTick(float deltaTime)
{
	Super::ManagerTick(deltaTime);
}

void UMyUMGManager::ManagerEnd()
{
	My_LOGCALLF(Log_Frame, Log);
	Super::ManagerEnd();
}

void UMyUMGManager::CreateUMG()
{
	My_LOGCALLF(Log_Frame, Log);

	//GetWorld()->localcon
	/*ConstructorHelpers::FClassFinder<UUIBattleMain> PutNameHere(TEXT("WidgetBlueprint'/Game/UI/BattleMainPanel.BattleMainPanel_C'"));
	if (PutNameHere.Class) {
		BattleMainClass = PutNameHere.Class;
	}*/
	//FStringClassReference HitEffectClass(TEXT("WidgetBlueprint'/Game/UI/BattleMainPanel.BattleMainPanel_C'"));
	//UClass* WidgetClass = HitEffectClass.TryLoadClass<UUserWidget>();

	//UUserWidget* Test = Cast<UUserWidget>(CreateWidget<UUserWidget>(GetWorld(), WidgetClass));
	//BattleMain = Cast<UUIBattleMain>(Test);

	////UUserWidget* UserWidget = Cast<UUserWidget>(BattleMain);
	//Test->AddToViewport();

	//Test->SetVisibility(ESlateVisibility::Hidden);

}

void UMyUMGManager::DestroyUMG()
{
	My_LOGCALLF(Log_Frame, Log);
}

//void UMyUMGManager::VisiblePannel(EUIPanel UIPanel, ESlateVisibility Visible)
//{
//	UUserWidget* UserWidget = nullptr;
//
//	switch (UIPanel)
//	{
//		case EUIPanel::None:
//
//			break;
//		case EUIPanel::BattleMainPanel:
//		{
//			UserWidget = Cast<UUserWidget>(BattleMain);
//		}
//		break;
//		default:
//			break;
//	}
//
//	if (UserWidget)
//	{
//		UserWidget->SetVisibility(Visible);
//	}
//	
//}