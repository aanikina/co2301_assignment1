// Fill out your copyright notice in the Description page of Project Settings.

#include "WalkableWall.h"

// Sets default values
AWalkableWall::AWalkableWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
	CollisionBoxComp->OnComponentEndOverlap.AddDynamic( this, &AWalkableWall::OnCollisionBoxOverlapEnd );

}

// Called every frame
void AWalkableWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWalkableWall::OnCollisionBoxOverlapBegin(
	UPrimitiveComponent *OverlappedComp,
	AActor *OtherActor,
	UPrimitiveComponent *OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult &SweepResult
) {
	
	UE_LOG( LogTemp, Warning, TEXT("--- AWalkableWall OnCollisionBoxOverlapBegin") );
	//GameModeRef->PointScored();

}

void AWalkableWall::OnCollisionBoxOverlapEnd(
	UPrimitiveComponent *OverlappedComp,
	AActor *OtherActor,
	UPrimitiveComponent *OtherComp,
	int32 OtherBodyIndex
) {
	
	UE_LOG( LogTemp, Warning, TEXT("--- AWalkableWall OnCollisionBoxOverlapEnd") );

}