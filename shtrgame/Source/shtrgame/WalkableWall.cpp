// Fill out your copyright notice in the Description page of Project Settings.

#include "WalkableWall.h"
#include "Engine/EngineTypes.h"

// Sets default values
AWalkableWall::AWalkableWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; // dont need tick

	// reused code from CO2301 lab4
	
	// initialize components
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>( TEXT("StaticMeshComponent") );
	CollisionBoxComp = CreateDefaultSubobject<UBoxComponent>( TEXT("CollisionBoxComponent") );
	
	// build component hierarchy
	SetRootComponent( StaticMeshComp );
	CollisionBoxComp->SetupAttachment( StaticMeshComp );

	// setup collision box
	CollisionBoxComp->SetBoxExtent( FVector( 10.0f, 10.0f, 10.0f ) );
	//CollisionBoxComp->SetRelativeLocation( FVector( 0.0f, 0.0f, 50.0f ) );
	CollisionBoxComp->SetCollisionProfileName( "Trigger" ); // all possible profile names are in unreal/projectsettings/collision

}

// Called when the game starts or when spawned
void AWalkableWall::BeginPlay()
{
	Super::BeginPlay();

	// reused code from CO2301 lab4
	
	// bind collision events
	CollisionBoxComp->OnComponentBeginOverlap.AddDynamic( this, &AWalkableWall::OnCollisionBoxOverlapBegin );

	// i dont use this
	//CollisionBoxComp->OnComponentEndOverlap.AddDynamic( this, &AWalkableWall::OnCollisionBoxOverlapEnd );

}

/*
// Called every frame
void AWalkableWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}*/

void AWalkableWall::OnCollisionBoxOverlapBegin(
	UPrimitiveComponent *OverlappedComp,
	AActor *OtherActor,
	UPrimitiveComponent *OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult &SweepResult
) {

	// make sure i collided with an actor that is being controlled
	if( OtherActor->GetInstigatorController() == nullptr ) {
		return;
	}

	// obtain my custom player controller
	// that is capable of remembering walls
	ACustomPlayerController *PlayerController = Cast<ACustomPlayerController>( OtherActor->GetInstigatorController() );

	if( PlayerController->LastUsedWall == this ) {
		// i already collided with this wall, not doing anything
		return;
	}
	
	UE_LOG( LogTemp, Log, TEXT("Player's LastUsedWall updated") );

	// remember this wall
	PlayerController->LastUsedWall = this;

	// snap player to this wall
	// help:
	// https://stackoverflow.com/questions/72888511/how-to-log-fvector-in-unreal-engine
	// https://forums.unrealengine.com/t/how-to-attach-an-actor-to-any-surface/467663/4
	// https://docs.unrealengine.com/4.27/en-US/API/Runtime/Engine/GameFramework/AActor/AttachToComponent/
	// https://forums.unrealengine.com/t/how-to-attach-components-maintaining-their-orientation/86433
	// https://d3kjluh73b9h9o.cloudfront.net/original/4X/d/c/7/dc762b96412ad0fe08ca6c9fa8c8f67047ed6629.jpeg

	FAttachmentTransformRules rules(
		EAttachmentRule::KeepWorld, // location
		EAttachmentRule::SnapToTarget, // rotation
		EAttachmentRule::KeepWorld, // scale
		true
		);

	OtherActor->AttachToActor(
		this,
		rules
		);
}

/*
void AWalkableWall::OnCollisionBoxOverlapEnd(
	UPrimitiveComponent *OverlappedComp,
	AActor *OtherActor,
	UPrimitiveComponent *OtherComp,
	int32 OtherBodyIndex
) {
	
	//UE_LOG( LogTemp, Warning, TEXT("--- AWalkableWall OnCollisionBoxOverlapEnd") );

}*/