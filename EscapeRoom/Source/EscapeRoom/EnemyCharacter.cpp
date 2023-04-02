// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"
#include "DodgeballProjectile.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);

	// Look at the player character every frame
	bCanSeePlayer = LookAtActor(PlayerCharacter);
	if (bCanSeePlayer != bPreviousCanSeePlayer)
	{
		if (bCanSeePlayer)
		{
			//Start throwing dodgeballs
			GetWorldTimerManager().SetTimer(ThrowTimerHandle,
				this,
				&AEnemyCharacter::ThrowDodgeball, ThrowingInterval,
				true,
				ThrowingDelay);
		}
		else
		{
			//Stop throwing dodgeballs
			GetWorldTimerManager().ClearTimer(ThrowTimerHandle);
		}
	}
	bPreviousCanSeePlayer = bCanSeePlayer;
}

// Called to bind functionality to input
bool AEnemyCharacter::LookAtActor(AActor* TargetActor) {

	if (TargetActor == nullptr) return false;

	if (CanSeeActor(TargetActor)) {
		//setting the location of the enemy and the target
		FVector Start = GetActorLocation();
		FVector End = TargetActor->GetActorLocation();
		//calculate rotation from start point to facing end point
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(Start, End);

		//set enemy rotation
		SetActorRotation(LookAtRotation);
		return true;
	}
	return false;
}
bool AEnemyCharacter::CanSeeActor(const AActor* const TargetActor) const {
	if (TargetActor == nullptr) return false;

	//Store the results of the Line Trace
	FHitResult Hit;

	//Where the Line Trace starts and ends
	FVector Start = GetActorLocation();
	FVector End = TargetActor->GetActorLocation();

	//The trace channel we want to compare against
	ECollisionChannel Channel = ECollisionChannel::ECC_Visibility;

	FCollisionQueryParams QueryParams;
	//Ignore the actor that's executing this Line Trace
	QueryParams.AddIgnoredActor(this);
	// And the target we're checking for
	QueryParams.AddIgnoredActor(TargetActor);

	//Execute the Line Trace
	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, Channel, QueryParams);

	//set the color Green if blocked or Red if not blocked
	FColor LineColor = (Hit.bBlockingHit) ? FColor::Green : FColor::Red;

	//Show the Line Trace inside the game
	DrawDebugLine(GetWorld(), Start, End, LineColor);

	return !Hit.bBlockingHit;
}
void AEnemyCharacter::ThrowDodgeball()
{
	if (DodgeballClass == nullptr)
	{
		return;
	}
	FVector ForwardVector = GetActorForwardVector();
	float SpawnDistance = 40.f;
	FVector SpawnLocation = GetActorLocation() + (ForwardVector *
		SpawnDistance);
	//Spawn new dodgeball
	GetWorld()->SpawnActor<ADodgeballProjectile>(DodgeballClass,
		SpawnLocation, GetActorRotation());
}

