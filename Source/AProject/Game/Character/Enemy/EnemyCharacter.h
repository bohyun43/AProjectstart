// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyCharacter.h"
#include "Character/Enemy/EnemyType.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEnemyCharacterDestory, AActor*, EnemyCharacter );

UCLASS()
class APROJECT_API AEnemyCharacter : public AMyCharacter
{
	GENERATED_BODY()
public:
	AEnemyCharacter();
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State" )
		EEnemyState CurrentState = EEnemyState::Normal;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
		EEnemyType EnemyType = EEnemyType::None;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
		EEnemyAttackType EnemyAttackType = EEnemyAttackType::None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
		class UBehaviorTree* EnemyBehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect")
		class UParticleSystem* HitEffect;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect")
		class UParticleSystem* HitEffect_Flamethrower;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect")
		class UParticleSystemComponent* Particle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
		float HitEffectScale;
public:
	UFUNCTION(BlueprintImplementableEvent)
		void DestoryActionEvent();

	UFUNCTION()
		void CheckDestory();

public:
	virtual float TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser) override;

	//Delegate
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FEnemyCharacterDestory	DestoryDelegate;	// ÆÄ±« ¾Ë¸²

	UFUNCTION()
	void AddDestoryDelegateByMissile(class AMyMissile* Actor);
public:
	void SetCurrentState(EEnemyState State);
	EEnemyState GetCurrentState() { return CurrentState; }
	class UBehaviorTree* GetEnemyBehaviorTree() { return EnemyBehaviorTree; }

	void SetEnemyType(EEnemyType Type);
	void SetMaxHP(float MaxHP) { /*StateHP.SetMaxHP(MaxHP);*/ }
	void SetAttackType(EEnemyAttackType Type) { EnemyAttackType = Type; }

	void SetDamage(float DamageAmount);
};
