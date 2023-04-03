// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DodgeballProjectile.generated.h"

UCLASS()
class ESCAPEROOM_API ADodgeballProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADodgeballProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//The sound the dodgeball will make when it bounces off of a surface
	UPROPERTY(EditAnywhere, Category = Sound)
		class USoundBase* BounceSound;

	// The sound attenuation of the previous sound
	UPROPERTY(EditAnywhere, Category = Sound)
		class USoundAttenuation* BounceSoundAttenuation;

	// The particle system the dodgeball will spawn when it hits the player
	UPROPERTY(EditAnywhere, Category = Particle)
		class UParticleSystem* HitParticles;

	//The sound the dodgeball will make when it hits the player
	UPROPERTY(EditAnywhere, Category = Sound)
		class USoundBase* DamageSound;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called when the object collides
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, FVector
			NormalImpulse, const
			FHitResult& Hit);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category =
		Dodgeball, meta = (AllowPrivateAccess = "true"))
		class USphereComponent* SphereComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category =
		Dodgeball, meta = (AllowPrivateAccess = "true"))
		class UProjectileMovementComponent* ProjectileMovement;

};
