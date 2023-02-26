// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneralGun.h"

// Sets default values
AGeneralGun::AGeneralGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
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

/*
// Called every frame
void AGeneralGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}*/

float AGeneralGun::GetFireCooldown() {

	return FireCooldown;

}

float AGeneralGun::GetFireDistance() {

	return FireDistance;

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

void AGeneralGun::FireCooldownTimerRanOut() {

	// this will allow to set this timer again
	FireCooldownTimerHandle.Invalidate();

}

bool AGeneralGun::FireTriggerPull() {

	//UE_LOG( LogTemp, Warning, TEXT("AGeneralGun::FireTriggerPull") );
	
	// monitor cooldown if i have one, skip if i don't
	// reused code from CO2301 lab 7
	
	if( FireCooldown>0.0f ) {

		// help:
		// https://docs.unrealengine.com/4.26/en-US/API/Runtime/Engine/Engine/FTimerHandle/
		if( FireCooldownTimerHandle.IsValid() ) {
			// timer is running, not doing anything
		
			if( FailedFireSound ) {
				UGameplayStatics::PlaySoundAtLocation(
				GetWorld(),
				FailedFireSound,
				GetActorLocation(),
				1.0f, 1.0f, 0.0f
				);
			}

			return false;
		}

		// timer is not running, this means
		// i have no cooldown yet
		// i want to start it and finish this attack

		GetWorld()->GetTimerManager().SetTimer(
			FireCooldownTimerHandle,
			this, // which object runs the timer
			&AGeneralGun::FireCooldownTimerRanOut, // what to do when the timer runs out
			FireCooldown, // timer duration
			false // loop the timer?
		);

	}

	// finish the attack

	// bam

	if( FireSound ) {
		UGameplayStatics::PlaySoundAtLocation(
		GetWorld(),
		FireSound,
		GetActorLocation(),
		1.0f, 1.0f, 0.0f
		);
	}

	// i want to spawn some shells at the same location
	
	FVector SpawnLocation = ShellSpawnPointSceneComp->GetComponentLocation();
	FRotator SpawnRotation = ShellSpawnPointSceneComp->GetComponentRotation();

	SpawnBulletShell( SpawnLocation, SpawnRotation );

	return true;

}

void AGeneralGun::FireTriggerRelease() {

	UE_LOG( LogTemp, Warning, TEXT("AGeneralGun::FireTriggerRelease") );

}

float AGeneralGun::GetDamage() {

	// Returns the exact damage this gun can cause.

	return BaseDamage; // no upgrades yet

}