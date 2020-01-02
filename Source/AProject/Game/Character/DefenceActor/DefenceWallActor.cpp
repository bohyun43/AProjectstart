// Fill out your copyright notice in the Description page of Project Settings.


#include "DefenceWallActor.h"
#include "Components/CapsuleComponent.h"
#include "TimerManager.h"
#include "Engine/World.h"
float ADefenceWallActor::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	DefenceWallState = EDefenceWallState::Attacked;
	//StateHP.TakeDamage(DamageAmount);

	//if (StateHP.GetCurrentHP() == 0)
	//{
	//	//GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//	DefenceWallState = EDefenceWallState::Destory;

	//	GetCapsuleComponent()->SetVisibility(false, true);
	//	
	//	//2ÃÊ ÈÄ ÆÄ±«
	//	FTimerHandle DestoryHandle;
	//	GetWorld()->GetTimerManager().SetTimer(DestoryHandle,
	//										   this,
	//										   &ADefenceWallActor::DestoryActor,
	//										   2.0f);
	//}
	return DamageAmount;
}

void ADefenceWallActor::DestoryActor()
{
	//Destroy();
}