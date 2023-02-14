// Fill out your copyright notice in the Description page of Project Settings.

#include "WalkableWall.h"

// Sets default values
AWalkableWall::AWalkableWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

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

void AWalkableWall::CheckPlaneEquation( AActor *OtherActor ) {

	// help:
	// http://mathprofi.ru/uravnenie_ploskosti.html

	// equation:
	// Ax + By + Cz = 0;



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

	// help:
	// https://stackoverflow.com/questions/72888511/how-to-log-fvector-in-unreal-engine

	///*
	FRotator OldRot = OtherActor->GetActorRotation();
	FRotator WallRot = GetActorRotation();
	FRotator FinalRot = FRotator( WallRot.Roll, OldRot.Yaw, WallRot.Pitch ); // ???
	
	UE_LOG( LogTemp, Warning, TEXT("--- AWalkableWall OnCollisionBoxOverlapBegin") );
	UE_LOG( LogTemp, Warning, TEXT("pawn rot: %s"), *OldRot.ToString() );
	UE_LOG( LogTemp, Warning, TEXT("wall rot: %s"), *GetActorRotation().ToString() );
	UE_LOG( LogTemp, Warning, TEXT("finalrot: %s"), *FinalRot.ToString() );

	OtherActor->SetActorRotation( FinalRot );
	//AddActorLocalRotation( DeltaRotation, true );

	//*/

}

void AWalkableWall::OnCollisionBoxOverlapEnd(
	UPrimitiveComponent *OverlappedComp,
	AActor *OtherActor,
	UPrimitiveComponent *OtherComp,
	int32 OtherBodyIndex
) {
	
	UE_LOG( LogTemp, Warning, TEXT("--- AWalkableWall OnCollisionBoxOverlapEnd") );

}