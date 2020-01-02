// Fill out your copyright notice in the Description page of Project Settings.

#include "MyTower.h"
#include "MyType.h"
#include "EnemySpawnManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TimerManager.h"

//#include "Character/Enemy/EnemyCharacter.h"
// Sets default values
AMyTower::AMyTower()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttackDamage = 1.0f;
	AttackSpeed = 1.0f;
	Radius = 200.0f;
	MaxTargetCount = 1;

	LODType = ELODType::LOD_0;
	Tags.Add(FName(TEXT("Tower")));
}

// Called when the game starts or when spawned
void AMyTower::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(UpdateGameHandle, this, &AMyTower::TowerUpdate, AttackSpeed );

	//FTimerHandle StartGameHandle;
	//GetWorldTimerManager().SetTimer(StartGameHandle, &AMyTower::TowerUpdate, 3.f, false);

	

}

// Called every frame
void AMyTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	USceneComponent*	Point = Cast<USceneComponent>(GetDefaultSubobjectByName(TEXT("Head")));
	if (Point && FFTargetActor)
	{
		FLerpTime += 2.0f * DeltaTime;
		FLerpTime = FMath::Clamp(FLerpTime, 0.0f, 1.0f);

		FVector Dir = FFTargetActor->GetActorLocation() - GetActorLocation();
		float Dot = FVector::DotProduct(FVector::ForwardVector, Dir.GetSafeNormal());
		FVector Cross = FVector::CrossProduct(FVector::ForwardVector, Dir.GetSafeNormal());
		float AcosAngle = FMath::Acos(Dot);
		float ResultAngle = FMath::RadiansToDegrees(AcosAngle);

		if (Cross.Z < 0.0f)
		{
			ResultAngle = 360 - ResultAngle;
		}

		FTestAngle = ResultAngle - 90.0f;


		float Angle = FMath::Lerp(FCurrentAngle, FTestAngle, FLerpTime);

		UE_LOG(LogClass,Warning , TEXT("Value%.2f"), FLerpTime);
		float DotUp = FVector::DotProduct(FVector::UpVector, Dir.GetSafeNormal());
		FVector CrossUp = FVector::CrossProduct(FVector::UpVector, Dir.GetSafeNormal());
		float AcosAngleUp = FMath::Acos(DotUp);
		float ResultAngleUp = FMath::RadiansToDegrees(AcosAngleUp);
		if (CrossUp.Z < 0.0f)
		{
			ResultAngleUp = 360 - ResultAngleUp;
		}

		ResultAngleUp = ResultAngleUp - 90;

		Point->SetWorldRotation(FRotator(0, Angle, ResultAngleUp), false, nullptr, ETeleportType::None);
		//Point->SetRelativeRotation(FRotator(0.0f, Angle, 0) , false , nullptr , ETeleportType::TeleportPhysics);
		FCurrentAngle = Angle;
	}
}
void AMyTower::TowerUpdate()
{
	#ifdef UE_EDITOR
	FVector MyPos = GetActorLocation();
	UKismetSystemLibrary::DrawDebugCircle(GetWorld(), MyPos, Radius, 50, FLinearColor(1.0f, 0.0f, 0.2f, 1.0f), 5.0f, 2.0f, FVector(1, 0, 0), FVector(0, 1, 0));
	#endif // UE_EDITOR

	// 타겟 검증
	FindTarget();

	float AttackUpdateSpeed = AttackSpeed;
	// 타겟이 있으면 AttackSpeed초 , 없으면 0.1초 마다 업데이트
	if (ArrTarget.Num() >= 1)
	{
		//SetActorTickInterval(AttackSpeed);
		OnFire();
	}
	else
	{
		AttackUpdateSpeed = 0.1;
		//SetActorTickInterval(0.1f);
	}

	GetWorldTimerManager().SetTimer(UpdateGameHandle, this, &AMyTower::TowerUpdate, AttackUpdateSpeed);


}
void AMyTower::FindTarget()
{
	FindTarget(Radius);
}
void AMyTower::FindTarget(float RadiusParam)
{
	TArray<AActor*> Remove;

		//GetWorld()->getactor

	for (auto Iter : ArrTarget)
	{
		AEnemyCharacter* Target = Cast<AEnemyCharacter>(Iter);
		if (Target)
		{
			if (Target->CurrentState == EEnemyState::Dead)
			{
				Remove.Add(Cast< AActor>(Target));
			}

			FVector EnemyPos = Target->GetActorLocation();
			FVector Sub = GetActorLocation() - EnemyPos;

			if (Sub.Size() >= RadiusParam)
			{
				Remove.Add(Cast< AActor>(Target));
				//UE_LOG(LogClass, Warning, TEXT("%s ::: %.2f"), *Actor->GetName(), Sub.Size());
			}
		}
	}


	for (auto Iter : Remove)
	{
		ArrTarget.Remove(Iter);
	}

	// 타겟 찾기.
	UEnemySpawnManager* SpawnMgr = MYGet()->GetEnemySpawn();
	if (SpawnMgr)
	{
		//TArray<AActor*> FoundActors;
		//UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyCharacter::StaticClass(), FoundActors);
		//for (auto Iter : FoundActors)
		for (auto Iter : SpawnMgr->EnemySpawn)
		{
			if (ArrTarget.Num() >= MaxTargetCount)
				continue;

			AEnemyCharacter* Actor = Cast<AEnemyCharacter>(Iter);
			if (Actor == nullptr)
				continue;

			if (Actor->CurrentState == EEnemyState::None)
				continue;

			if (Actor->CurrentState == EEnemyState::Dead)
				continue;

			int32 Index = 0;
			if (ArrTarget.Find(Actor, Index) == true)
				continue;

			FVector EnemyPos = Actor->GetActorLocation();
			FVector Sub = GetActorLocation() - EnemyPos;

			if (Sub.Size() < RadiusParam)
			{
				ArrTarget.Add(Actor);
				//UE_LOG(LogClass, Warning, TEXT("%s ::: %.2f"), *Actor->GetName(), Sub.Size());
			}
		}
	}
}
// Called to bind functionality to input
void AMyTower::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyTower::OnFire()
{

}

FTransform AMyTower::GetShootTransform()
{
	UStaticMeshComponent* Point = GetShootPointComponent();
	if (Point == nullptr)
		return FTransform::Identity;

	ShootPoint = Point->GetComponentTransform();
	ShootPoint.SetScale3D(FVector(MuzzleFlashScale, MuzzleFlashScale, MuzzleFlashScale));

	return ShootPoint;
}

UStaticMeshComponent* AMyTower::GetShootPointComponent()
{
	UStaticMeshComponent* Point = Cast<UStaticMeshComponent>(GetDefaultSubobjectByName(TEXT("ShootPoint")));

	return Point;
}