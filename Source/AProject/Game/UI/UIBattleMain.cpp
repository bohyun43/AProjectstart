// Fill out your copyright notice in the Description page of Project Settings.


#include "UIBattleMain.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Battle/MyBattleGameStateBase.h"

UUIBattleMain::UUIBattleMain(const FObjectInitializer& ObjectInitializer) : UMyWidgetBase(ObjectInitializer)
{

}

bool UUIBattleMain::Initialize()
{
	Super::Initialize();

	GameLevel = EGameLevel::Easy;
	return true;
}
void UUIBattleMain::NativeConstruct()
{
	CardWidget_0 = Cast<UUserWidget>(GetWidgetFromName(TEXT("Card_0")));
	CardWidget_1 = Cast<UUserWidget>(GetWidgetFromName(TEXT("Card_1")));
	CardWidget_2 = Cast<UUserWidget>(GetWidgetFromName(TEXT("Card_2")));
	CardWidget_3 = Cast<UUserWidget>(GetWidgetFromName(TEXT("Card_3")));
	CardWidget_4 = Cast<UUserWidget>(GetWidgetFromName(TEXT("Card_4")));

	DoneBtn = Cast< UButton>(GetWidgetFromName(TEXT("Done")));
	//UWidget* Change = Card_0->WidgetTree->FindWidget(TEXT("ChangeButton"));

	UWidget* Change = CardWidget_0->GetWidgetFromName("ChangeButton");
	if (Change)
	{
		ChangeBtn_0 = Cast<UButton>(Change);
		ChangeBtn_0->OnClicked.AddDynamic(this, &UUIBattleMain::OnChangeCard0);
	}


	Change = CardWidget_1->GetWidgetFromName("ChangeButton");
	if (Change)
	{
		ChangeBtn_1 = Cast<UButton>(Change);
		ChangeBtn_1->OnClicked.AddDynamic(this, &UUIBattleMain::OnChangeCard1);
	}


	Change = CardWidget_2->GetWidgetFromName("ChangeButton");
	if (Change)
	{
		ChangeBtn_2 = Cast<UButton>(Change);
		ChangeBtn_2->OnClicked.AddDynamic(this, &UUIBattleMain::OnChangeCard2);
	}


	Change = CardWidget_3->GetWidgetFromName("ChangeButton");
	if (Change)
	{
		ChangeBtn_3 = Cast<UButton>(Change);
		ChangeBtn_3->OnClicked.AddDynamic(this, &UUIBattleMain::OnChangeCard3);
	}


	Change = CardWidget_4->GetWidgetFromName("ChangeButton");
	if (Change)
	{
		ChangeBtn_4 = Cast<UButton>(Change);
		ChangeBtn_4->OnClicked.AddDynamic(this, &UUIBattleMain::OnChangeCard4);
	}
	// 카드 기본 덱 셋팅
	for (int Type = 0; Type < (int)ECardType::Max; ++Type)
	{
		for (int Number = 1; Number < 14; ++Number)
		{
			FCard Card;
			Card.CardType = (ECardType)Type;
			Card.Number = Number;

			Deck.Add(Card);
		}
	}

	ResetCard();


	DoneBtn->OnClicked.AddDynamic(this, &UUIBattleMain::OnDone);

}

void UUIBattleMain::OnChangeCard(UUserWidget* SlotCard)
{
	ChangeCard(SlotCard);
}


void UUIBattleMain::OnChangeCard0()
{
	OnChangeCard(CardWidget_0);
}

void UUIBattleMain::OnChangeCard1()
{
	OnChangeCard(CardWidget_1);
}

void UUIBattleMain::OnChangeCard2()
{
	OnChangeCard(CardWidget_2);
}

void UUIBattleMain::OnChangeCard3()
{
	OnChangeCard(CardWidget_3);
}

void UUIBattleMain::OnChangeCard4()
{
	OnChangeCard(CardWidget_4);
}

void UUIBattleMain::OnDone()
{	
	ECardRule CardRule = CheckCard();

	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("ECardRule"), true);
	FString Str = TEXT("Result : ") + EnumPtr->GetEnumName((int32)CardRule);

	UKismetSystemLibrary::PrintString(GetWorld(), Str);

	//this->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	//AMyGameState* TheGameState = Cast<AMyGameState>(GetWorld()->GetGameState());

	AMyBattleGameStateBase* TheGameState = Cast<AMyBattleGameStateBase>(GetWorld()->GetGameState());
	if (TheGameState)
	{
		TheGameState->SetGamePlayState(EGamePlayState::Defence);
	}
	//ResetCard();
}

void UUIBattleMain::ResetCard()
{
	Used.Reset();

	ChangeCard(CardWidget_0, true);
	ChangeCard(CardWidget_1, true);
	ChangeCard(CardWidget_2, true);
	ChangeCard(CardWidget_3, true);
	ChangeCard(CardWidget_4, true);
}
FCard UUIBattleMain::GetRandomCard()
{
	int64 Type = UKismetMathLibrary::RandomInteger64(4);
	int64 Number = UKismetMathLibrary::RandomInteger64(13) + 1;

	FCard Result;
	Result.CardType = (ECardType)Type;
	Result.Number = Number;

	bool CheckNumber = false;


	if (GameLevel == EGameLevel::Easy && Number >= 2 && Number <= 6)
	{
		Result = GetRandomCard();
	}
	//for (auto& Elem : Used)
	//{
	//	//if( Number <= 2 && )
	//	if (Elem.Number == Number && Elem.CardType == (ECardType)Type)
	//	{
	//		Result = GetRandomCard();
	//	}
	//}

	for (auto& Elem : MyCard)
	{
		FCard Card = Elem.Value;
		//if( Number <= 2 && )
		if (Card.Number == Number && Card.CardType == (ECardType)Type)
		{
			Result = GetRandomCard();
		}
	}

	return Result;
}
void UUIBattleMain::ChangeCard(UUserWidget* Card, bool AddUsed/* = false*/)
{
	UWidget* Clubs = Card->GetWidgetFromName("Clubs");
	UWidget* Spades = Card->GetWidgetFromName("Spades");
	UWidget* Hearts = Card->GetWidgetFromName("Hearts");
	UWidget* Diamonds = Card->GetWidgetFromName("Diamonds");

	Clubs->SetVisibility(ESlateVisibility::Hidden);
	Spades->SetVisibility(ESlateVisibility::Hidden);
	Hearts->SetVisibility(ESlateVisibility::Hidden);
	Diamonds->SetVisibility(ESlateVisibility::Hidden);

	// 랜덤 카드 얻기
	FCard Result = GetRandomCard();

	
	if (AddUsed == true)
	{
		Used.Add(Result);
	}

	// 현재 들고 있는 카드
	if (CardWidget_0 == Card)
	{
		MyCard.Add(0, Result);
	}
	else if (CardWidget_1 == Card)
	{
		MyCard.Add(1, Result);
	}
	else if (CardWidget_2 == Card)
	{
		MyCard.Add(2, Result);
	}
	else if (CardWidget_3 == Card)
	{
		MyCard.Add(3, Result);
	}
	else if (CardWidget_4 == Card)
	{
		MyCard.Add(4, Result);
	}


	UWidget* Select = nullptr;

	switch (Result.CardType)
	{
		case ECardType::Spades:
		{
			Select = Spades;
		}
		break;
		case ECardType::Clubs:
		{
			Select = Clubs;
		}
		break;
		case ECardType::Hearts:
		{
			Select = Hearts;
		}
		break;
		case ECardType::Diamonds:
		{
			Select = Diamonds;
		}
		break;
		default:
			break;
	}

	if (Select != nullptr)
	{
		Select->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		UUserWidget* UserWidget = Cast<UUserWidget>(Select);
		if (UserWidget)
		{
			UWidget* NumberWidget = UserWidget->GetWidgetFromName("Number");

			if (NumberWidget)
			{
				UTextBlock* Text = Cast<UTextBlock>(NumberWidget);

				if (Text)
				{
					FString Str = "";
					if (Result.Number == 1)
					{
						Str = "A";
					}
					else if (Result.Number == 11)
					{
						Str = "J";
					}
					else if (Result.Number == 12)
					{
						Str = "Q";
					}
					else if (Result.Number == 13)
					{
						Str = "K";
					}
					else
					{
						Str = FString::FromInt(Result.Number);
					}

					Text->SetText(FText::FromString(Str));
				}
			}
		}
		
	}
	

}

ECardRule UUIBattleMain::CheckCard()
{
	bool Result = false;

	Result = RoyalStraightFlush();
	if (Result == true)
	{
		return ECardRule::RoyalStraightFlush;
	}
	Result = BackStraightFlush();
	if (Result == true)
	{
		return ECardRule::BackStraightFlush;
	}
	Result = StraightFlush();
	if (Result == true)
	{
		return ECardRule::StraightFlush;
	}
	Result = FourofaKind();
	if (Result == true)
	{
		return ECardRule::FourofaKind;
	}
	Result = FullHouse();
	if (Result == true)
	{
		return ECardRule::FullHouse;
	}
	Result = Flush();
	if (Result == true)
	{
		return ECardRule::Flush;
	}
	Result = Mountain();
	if (Result == true)
	{
		return ECardRule::Mountain;
	}
	Result = BackStraight();
	if (Result == true)
	{
		return ECardRule::BackStraight;
	}
	Result = Straight();
	if (Result == true)
	{
		return ECardRule::Straight;
	}
	Result = TreeofaKind();
	if (Result == true)
	{
		return ECardRule::TreeofaKind;
	}
	Result = TwoPair();
	if (Result == true)
	{
		return ECardRule::TwoPair;
	}
	Result = AceOnePair();
	if (Result == true)
	{
		return ECardRule::AceOnePair;
	}
	Result = OnePair();
	if (Result == true)
	{
		return ECardRule::OnePair;
	}
	Result = NoPair();
	if (Result == true)
	{
		return ECardRule::NoPair;
	}

	return ECardRule::NoPair;
}

bool UUIBattleMain::RoyalStraightFlush()
{

	bool IsFlush = Flush();

	if (IsFlush == false)
	{
		return false;
	}

	bool IsMountain = Mountain();

	return IsMountain;
}
bool UUIBattleMain::StraightFlush()
{
	TSet<int64> Result;

	bool IsFlush = Flush();

	if (IsFlush == false)
	{
		return false;
	}

	bool IsStraight = GetStraightData(Result);

	if (IsStraight == false)
	{
		return false;
	}

	return true;
}
bool UUIBattleMain::BackStraightFlush()
{
	bool IsFlush = Flush();

	if (IsFlush == false)
	{
		return false;
	}

	bool IsBackStraight = BackStraight();

	return IsBackStraight;
}
bool UUIBattleMain::FourofaKind()
{
	ECardType CardType = ECardType::Max;

	for (auto& Parent : MyCard)
	{
		int64 Count = 0;

		FCard ParentCard = Parent.Value;
		for (auto& Child : MyCard)
		{
			FCard ChildCard = Child.Value;
			//Result.Add(IterCard.Number);

			if (ParentCard.Number == ChildCard.Number)
			{
				++Count;
			}
		}

		if (Count == 4)
		{
			return true;
		}
	}

	return false;
}
bool UUIBattleMain::FullHouse()
{
	ECardType CardType = ECardType::Max;

	int64 Number0 = 0;
	int64 Number1 = 0;

	int64 Count0 = 0;
	int64 Count1 = 0;

	bool bCheckChange = false;
	for (auto& Parent : MyCard)
	{
		FCard ParentCard = Parent.Value;

		if (Number0 == 0)
		{
			bCheckChange = false;
			Number0 = ParentCard.Number;
		}
		else if (Number0 == ParentCard.Number)
		{
			continue;
		}
		else if (Number1 == 0)
		{
			bCheckChange = true;
			Number1 = ParentCard.Number;
		}
		else if (Number1 == ParentCard.Number)
		{
			continue;
		}
		else
		{
			return false;
		}
	
		
		for (auto& Child : MyCard)
		{
			FCard ChildCard = Child.Value;

			if (bCheckChange == false)
			{
				if (Number0 == ChildCard.Number)
				{
					++Count0;
				}
			}
			else
			{
				if (Number1 == ChildCard.Number)
				{
					++Count1;
				}
			}

		}
	}

	if (Count0 + Count1 == 5)
	{
		return true;
	}

	return false;
}
bool UUIBattleMain::Flush()
{
	ECardType CardType = ECardType::Max;

	for (auto& Elem : MyCard)
	{
		FCard IterCard = Elem.Value;

		if (CardType == ECardType::Max)
		{
			CardType = IterCard.CardType;
		}
		else
		{
			if (CardType != IterCard.CardType)
			{
				return false;
			}
		}
	}

	return true;
}
bool UUIBattleMain::Mountain()
{
	bool bNumber1 = false;
	bool bNumber10 = false;
	bool bNumber11 = false;
	bool bNumber12 = false;
	bool bNumber13 = false;

	TSet<int64> Result;
	bool IsStraight = GetStraightData(Result);

	if (IsStraight == false)
	{
		return false;
	}

	for (auto& Elem : Result)
	{
		int64 IterCardNumber = Elem;

		switch (IterCardNumber)
		{
			case 1:
			{
				if (bNumber1 == true)
				{
					return false;
				}

				bNumber1 = true;
			}
			break;
			case 10:
			{
				if (bNumber10 == true)
				{
					return false;
				}

				bNumber10 = true;
			}
			break;
			case 11:
			{
				if (bNumber11 == true)
				{
					return false;
				}

				bNumber11 = true;
			}
			break;
			case 12:
			{
				if (bNumber12 == true)
				{
					return false;
				}

				bNumber12 = true;
			}
			break;
			case 13:
			{
				if (bNumber13 == true)
				{
					return false;
				}

				bNumber13 = true;
			}
			break;
			default:
			{
				return false;
			}
			break;
		}
	}

	if (bNumber1 == true
		&& bNumber10 == true
		&& bNumber11 == true
		&& bNumber12 == true
		&& bNumber13 == true)
	{
		return true;
	}

	return false;
}
bool UUIBattleMain::GetStraightData(TSet<int64>& SetValue)
{
	TSet<int64> Result;

	//ECardType CardType = ECardType::Max;

	for (auto& Elem : MyCard)
	{
		FCard IterCard = Elem.Value;
		Result.Add(IterCard.Number);
	}

	Result.Sort([](const int64& A, const int64& B)
	{
		return A < B;
	});

	int64 CheckNumber = -1;

	for (auto& Elem : Result)
	{
		int64 IterCardNumber = Elem;

		if (CheckNumber == -1)
		{
			CheckNumber = IterCardNumber;
		}
		else
		{
			//**** 여러번 테스트가 필요할듯 하다..
			//* Easy 모드는 1 7~13 까지 2~6의 카드가 없다.
			// 
			if (GameLevel == EGameLevel::Easy && CheckNumber == 1)
			{
				// 로열 스트레이트 체크
				if (IterCardNumber == 10)
				{
					CheckNumber = 9;
				}
				//백 스트레이트 체크
				else if (IterCardNumber == 7)
				{
					CheckNumber = 6;
				}
			}

			++CheckNumber;

			if (CheckNumber != IterCardNumber)
			{
				return false;
			}
		}
	}

	SetValue = Result;

	return true;
}
bool UUIBattleMain::Straight()
{
	TSet<int64> Result;

	bool bCheck = GetStraightData(Result);

	return bCheck;
}
bool UUIBattleMain::BackStraight()
{
	TSet<int64> Result;

	bool IsStraight = GetStraightData(Result);

	if (IsStraight == false)
	{
		return false;
	}

	bool bNumber1 = false;
	bool bNumber2 = false;
	bool bNumber3 = false;
	bool bNumber4 = false;
	bool bNumber5 = false;


	for (auto& Elem : Result)
	{
		int64 IterCardNumber = Elem;

		switch (GameLevel)
		{
			case EGameLevel::Easy:
			{
				if (IterCardNumber != 1)
				{
					IterCardNumber = IterCardNumber - 5;
				}
			}
			break;
		}

		switch (IterCardNumber)
		{
			case 1:
			{
				if (bNumber1 == true)
				{
					return false;
				}
				bNumber1 = true;
			}
			break;
			case 2:
			{
				if (bNumber2 == true)
				{
					return false;
				}
				bNumber2 = true;
			}
			break;
			case 3:
			{
				if (bNumber3 == true)
				{
					return false;
				}
				bNumber3 = true;
			}
			break;
			case 4:
			{
				if (bNumber4 == true)
				{
					return false;
				}

				bNumber4 = true;
			}
			break;
			case 5:
			{
				if (bNumber5 == true)
				{
					return false;
				}

				bNumber5 = true;
			}
			break;
			default:
			{
				return false;
			}
			break;
		}
	}

	if (bNumber1 == true
		&& bNumber2 == true
		&& bNumber3 == true
		&& bNumber4 == true
		&& bNumber5 == true)
	{
		return true;
	}

	return false;
}
bool UUIBattleMain::TreeofaKind()
{
	for (auto& Parent : MyCard)
	{
		int64 Count = 0;

		FCard ParentCard = Parent.Value;
		for (auto& Child : MyCard)
		{
			FCard ChildCard = Child.Value;

			if (ParentCard.Number == ChildCard.Number)
			{
				++Count;
			}
		}

		if (Count == 3)
		{
			return true;
		}
	}
	return false;
}
bool UUIBattleMain::TwoPair()
{
	ECardType CardType = ECardType::Max;

	int64 Number0 = 0;
	int64 Number1 = 0;
	int64 Number2 = 0;

	int64 Count0 = 0;
	int64 Count1 = 0;
	int64 Count2 = 0;

	bool bCheckChange0 = false;
	bool bCheckChange1 = false;
	for (auto& Parent : MyCard)
	{
		FCard ParentCard = Parent.Value;

		if (Number0 == 0)
		{
			bCheckChange0 = false;
			Number0 = ParentCard.Number;
		}
		else if (Number0 == ParentCard.Number)
		{
			continue;
		}
		else if (Number1 == 0)
		{
			bCheckChange0 = true;
			Number1 = ParentCard.Number;
		}
		else if (Number1 == ParentCard.Number)
		{
			continue;
		}
		else if (Number2 == 0)
		{
			bCheckChange1 = true;
			Number2 = ParentCard.Number;
		}
		else if (Number2 == ParentCard.Number)
		{
			continue;
		}
		else
		{
			return false;
		}


		for (auto& Child : MyCard)
		{
			FCard ChildCard = Child.Value;

			if (bCheckChange0 == false && bCheckChange1 == false)
			{
				if (Number0 == ChildCard.Number)
				{
					++Count0;
				}
			}
			else if (bCheckChange0 == true && bCheckChange1 == false)
			{
				if (Number1 == ChildCard.Number)
				{
					++Count1;
				}
			}
			else if (bCheckChange0 == true && bCheckChange1 == true)
			{
				if (Number2 == ChildCard.Number)
				{
					++Count2;
				}
			}
		}
	}

	int8 Result = 0;
	if (Count0 == 2)
	{
		Result += Count0;
	}

	if (Count1 == 2)
	{
		Result += Count1;
	}

	if (Count2 == 2)
	{
		Result += Count2;
	}

	if (Result == 4)
	{
		return true;
	}

	return false;
}
bool UUIBattleMain::AceOnePair()
{
	bool IsAce = false;
	int8 MaxCount = 0;
	for (auto& Parent : MyCard)
	{
		int64 Count = 0;

		FCard ParentCard = Parent.Value;
		for (auto& Child : MyCard)
		{
			FCard ChildCard = Child.Value;

			if (ParentCard.Number == ChildCard.Number)
			{
				++Count;

				if (ParentCard.Number == 1 && Count == 2)
				{
					IsAce = true;
				}
			}
		}

		if (MaxCount < Count)
		{
			MaxCount = Count;
		}
	}

	if (MaxCount == 2 && IsAce == true )
	{
		return true;
	}

	return false;
}

bool UUIBattleMain::OnePair()
{
	bool IsAce = false;
	int8 MaxCount = 0;
	for (auto& Parent : MyCard)
	{
		int64 Count = 0;

		FCard ParentCard = Parent.Value;
		for (auto& Child : MyCard)
		{
			FCard ChildCard = Child.Value;

			if (ParentCard.Number == ChildCard.Number)
			{
				++Count;
			}
		}

		if (MaxCount < Count)
		{
			MaxCount = Count;
		}
	}

	if (MaxCount == 2)
	{
		return true;
	}

	return false;
}
bool UUIBattleMain::NoPair()
{
	int8 MaxCount = 0;
	for (auto& Parent : MyCard)
	{
		int64 Count = 0;

		FCard ParentCard = Parent.Value;
		for (auto& Child : MyCard)
		{
			FCard ChildCard = Child.Value;

			if (ParentCard.Number == ChildCard.Number)
			{
				++Count;
			}
		}

		if (MaxCount < Count)
		{
			MaxCount = Count;
		}
	}

	if (MaxCount == 1)
	{
		return true;
	}

	return false;
}