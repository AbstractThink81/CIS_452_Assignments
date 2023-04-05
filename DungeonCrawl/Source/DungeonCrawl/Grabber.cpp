// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//FRotator MyRotation = GetComponentRotation();
	//FString RotationString = MyRotation.ToCompactString();
	//UE_LOG(LogTemp, Display, TEXT("Grabber Rotation: %s"), *RotationString)
	UPhysicsHandleComponent* PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr) {
		return;
	}


	if (PhysicsHandle->GetGrabbedComponent() != nullptr)
	{
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}
}
//use ctrl + period to quickly implement functions
void UGrabber::Grab()
{
	//TODO: make this into a UPROPERTY that is set at BeginPlay()
	UPhysicsHandleComponent* PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr) {
		return;
	}

	//draw a debug line forward from the player
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxGrabDistance;
	DrawDebugLine(GetWorld(), Start, End, FColor::Red);

	//GeometrySweep using sphere
	//sphere used for sweep
	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);

	//variables to hold the results of the sweep
	FHitResult HitResult;

	//The geometry sweep
	bool hasHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		Start,
		End,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		Sphere
	);
	/*
	if (hasHit) {
		DrawDebugSphere(GetWorld(), HitResult.Location, 10, 10, FColor::Green, false, 10);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 10, FColor::Red, false, 10);

		FString HitActorName = HitResult.GetActor()->GetActorNameOrLabel();
		UE_LOG(LogTemp, Display, TEXT("Hit actor's name: %s"), *HitActorName);
	}
	else {
		UE_LOG(LogTemp, Display, TEXT("No actor hit"));

	}
	*/
	if (hasHit) {
		//wake up the object we are grabbing
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		HitComponent->WakeAllRigidBodies();
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			HitComponent,
			NAME_None,
			HitResult.ImpactPoint,
			GetComponentRotation()
		);
	}
}

void UGrabber::Release()
{
	//UE_LOG(LogTemp, Display, TEXT("Released grabber"));
	UPhysicsHandleComponent* PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr) {
		return;
	}

	if (PhysicsHandle->GetGrabbedComponent() != nullptr) {
		PhysicsHandle->GetGrabbedComponent()->WakeAllRigidBodies();
		PhysicsHandle->ReleaseComponent();
	}
}

