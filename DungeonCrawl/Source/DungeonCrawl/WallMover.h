// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WallMover.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONCRAWL_API UWallMover : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWallMover();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
		FVector MoveOffset = FVector(0, 0, 600);
	UPROPERTY(EditAnywhere)
		float MoveTime = 4;
	UPROPERTY(EditAnywhere)
		bool MoveTriggered = false;

	FVector StartingLocation;

	UFUNCTION(BlueprintCallable)
		void SetMoveTriggered(bool NewMoveTriggered);
		
};
