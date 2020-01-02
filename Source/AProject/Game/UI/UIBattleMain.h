// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Frame/UMG/MyWidgetBase.h"
#include "MyType.h"
#include "UIBattleMain.generated.h"




USTRUCT(BlueprintType)
struct APROJECT_API FCard// : public UObject
{
	GENERATED_USTRUCT_BODY()

	FCard()
	{
		CardType = ECardType::Spades;
		Number = 0;
	}
	//virtual ~FStateHP() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
		ECardType CardType;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
		int64 Number = 0;

	bool operator== (const FCard& Other) const
	{
		return Number == Other.Number;
	}

	friend uint32 GetTypeHash(const FCard& Other)
	{
		return GetTypeHash(Other.CardType);
	}
};
/**
 * 
 */
UCLASS()
class APROJECT_API UUIBattleMain : public UMyWidgetBase
{
	GENERATED_BODY()
public:
	UUIBattleMain(const FObjectInitializer& ObjectInitializer);
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSet<FCard> Deck;	// Full Card

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSet<FCard> Used;	// 사용한 덱

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TMap<uint8,FCard> MyCard;	// 현재 자신의 카드

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EGameLevel	GameLevel;
public:
	virtual bool Initialize() override;
	virtual void NativeConstruct() override;

	UFUNCTION()
		FCard GetRandomCard();
	UFUNCTION()
		void OnChangeCard(UUserWidget* SlotCard);
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UButton* ChangeBtn_0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UButton* ChangeBtn_1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UButton* ChangeBtn_2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UButton* ChangeBtn_3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UButton* ChangeBtn_4;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UButton* DoneBtn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UUserWidget* CardWidget_0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UUserWidget* CardWidget_1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UUserWidget* CardWidget_2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UUserWidget* CardWidget_3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UUserWidget* CardWidget_4;

	UFUNCTION()
		void OnChangeCard0();
	UFUNCTION()
		void OnChangeCard1();
	UFUNCTION()
		void OnChangeCard2();
	UFUNCTION()
		void OnChangeCard3();
	UFUNCTION()
		void OnChangeCard4();
	UFUNCTION()
		void OnDone();

	void ResetCard();


private:
	UFUNCTION()
		void ChangeCard(UUserWidget* Card , bool AddUsed = false );

	UFUNCTION()
		ECardRule CheckCard();


	bool RoyalStraightFlush();
	bool StraightFlush();
	bool BackStraightFlush();
	bool FourofaKind();
	bool FullHouse();
	bool Flush();
	bool Mountain();
	bool Straight();
	bool BackStraight();
	bool TreeofaKind();
	bool TwoPair();
	bool AceOnePair();
	bool OnePair();
	bool NoPair();

	bool GetStraightData(TSet<int64>& SetValue);
};
