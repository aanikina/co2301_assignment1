// Fill out your copyright notice in the Description page of Project Settings.


#include "Teabag.h"

// Sets default values
ATeabag::ATeabag()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// reused code from CO2301 lab 3
	
	// initialize components

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>( TEXT("StaticMeshComponent") );
	
	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>( TEXT("ProjectileMovementComponent") );

	// build component hierarchy
	SetRootComponent( StaticMeshComp );

	// allow physics
	StaticMeshComp->SetNotifyRigidBodyCollision( true );
	StaticMeshComp->SetSimulatePhysics( true );
	
	// projectile movement
	ProjectileMovementComp->MaxSpeed = MovementSpeed;
	ProjectileMovementComp->InitialSpeed = MovementSpeed;
	InitialLifeSpan = InitialProjectileLifespan;

}

// Called when the game starts or when spawned
void ATeabag::BeginPlay()
{
	Super::BeginPlay();
	
	// reused code from CO2301 lab 3
	
	// bind events
	OnActorHit.AddDynamic( this, &ATeabag::OnHit );

}

// Called every frame
void ATeabag::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATeabag::OnHit( AActor *SelfActor, AActor *OtherActor, FVector NormalImpulse, const FHitResult &Hit ) {
	
	// reused code from CO2301 lab 3

	// NormalImpulse = velocity of the collision

	//bool bHitSaucer;

	//bHitSaucer = OtherActor->GetClass()->IsChildOf( ASaucer::StaticClass() );

	/*
	if( bHitSaucer ) {

		AActor* ProjectileOwner = GetOwner();
		if( ProjectileOwner == NULL ) { return; }
	
		//UE_LOG( LogTemp, Warning, TEXT( "------- teabag OnHit") );

		UGameplayStatics::ApplyDamage(
			OtherActor,
			BaseDamage,
			ProjectileOwner->GetInstigatorController(),
			this, // actor that caused damage
			UDamageType::StaticClass() // class that describes the damage that was done
		);

		Destroy();

	}*/

}
