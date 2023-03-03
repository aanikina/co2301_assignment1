// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneralShell.h"

// Sets default values
AGeneralShell::AGeneralShell()
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
	ProjectileMovementComp->MaxSpeed = FallSpeed*5.0f;
	ProjectileMovementComp->InitialSpeed = FallSpeed;
	InitialLifeSpan = InitialProjectileLifespan;

}

// Called when the game starts or when spawned
void AGeneralShell::BeginPlay()
{
	Super::BeginPlay();
	
	// bind events
	OnActorHit.AddDynamic( this, &AGeneralShell::OnHit );
	
}

// Called every frame
void AGeneralShell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGeneralShell::OnHit( AActor *SelfActor, AActor *OtherActor, FVector NormalImpulse, const FHitResult &Hit ) {
	
	//UE_LOG( LogTemp, Warning, TEXT("shell fell to the ground") );

	// reused code from CO2301 lab 3

	// NormalImpulse = velocity of the collision

	//UE_LOG( LogTemp, Warning, TEXT("AGeneralShell::OnHit -- damaged actor %s"), OtherActor );

	if( !OtherActor ) {
		return;
	}

	// make sure i hit something controllable
	if( !OtherActor->GetInstigatorController() ) {
		return;
		}

	UGameplayStatics::ApplyDamage(
		OtherActor,
		BaseDamage,
		OtherActor->GetInstigatorController(), // you hurt yourself
		this, // actor that caused damage
		UDamageType::StaticClass() // class that describes the damage that was done
	);

	Destroy();

}
