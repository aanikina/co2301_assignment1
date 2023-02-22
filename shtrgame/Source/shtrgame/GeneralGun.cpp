// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneralGun.h"

// Sets default values
AGeneralGun::AGeneralGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// reused code from CO2301 lab 3
	
	// initialize components

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>( TEXT("StaticMeshComponent") );
	ShellSpawnPointSceneComp = CreateDefaultSubobject<USceneComponent>( TEXT("ShellSpawnPointSceneComp") );
	
	// build component hierarchy
	SetRootComponent( StaticMeshComp );

	ShellSpawnPointSceneComp->SetupAttachment( StaticMeshComp );

}

// Called when the game starts or when spawned
void AGeneralGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGeneralGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGeneralGun::SpawnBulletShell() {

	// reused code from CO2301 lab

	if( BulletShellClass ) {
	
		FVector SpawnLocation = ShellSpawnPointSceneComp->GetComponentLocation();
		FRotator SpawnRotation = ShellSpawnPointSceneComp->GetComponentRotation();
		AGeneralShell* BulletShell = GetWorld()->SpawnActor<AGeneralShell>( BulletShellClass, SpawnLocation, SpawnRotation );

	}

}

void AGeneralGun::SpawnBulletShell( FVector &SpawnLocation, FRotator &SpawnRotation ) {

	// reused code from CO2301 lab

	if( BulletShellClass ) {
	
		AGeneralShell* BulletShell = GetWorld()->SpawnActor<AGeneralShell>( BulletShellClass, SpawnLocation, SpawnRotation );

	}

}

void AGeneralGun::FireTriggerPull() {

	UE_LOG( LogTemp, Warning, TEXT("AGeneralGun::FireTriggerPull") );

	// i want to spawn a shell
	
	FVector SpawnLocation = ShellSpawnPointSceneComp->GetComponentLocation();
	FRotator SpawnRotation = ShellSpawnPointSceneComp->GetComponentRotation();

	SpawnBulletShell( SpawnLocation, SpawnRotation );

}

void AGeneralGun::FireTriggerRelease() {

	UE_LOG( LogTemp, Warning, TEXT("AGeneralGun::FireTriggerRelease") );

}
