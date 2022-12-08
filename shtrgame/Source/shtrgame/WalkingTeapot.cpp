// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "WalkingTeapot.h"

// Sets default values
AWalkingTeapot::AWalkingTeapot()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// reused code from CO2301 lab2
	
	// initialize components
	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>( TEXT("SkeletalMeshComponent") );
	CameraComp = CreateDefaultSubobject<UCameraComponent>( TEXT("CameraComponent") );
	CameraSpringArmComp = CreateDefaultSubobject<USpringArmComponent>( TEXT("CameraSpringArmComponent") );
	ProjectileSpawnPointSceneComp = CreateDefaultSubobject<USceneComponent>( TEXT("ProjectileSpawnPointComponent") );
	
	// build component hierarchy

	SetRootComponent( SkeletalMeshComp );

	CameraSpringArmComp->SetupAttachment( SkeletalMeshComp );
	CameraComp->SetupAttachment( CameraSpringArmComp, USpringArmComponent::SocketName );

	ProjectileSpawnPointSceneComp->SetupAttachment( SkeletalMeshComp );
	ProjectileSpawnPointSceneComp->SetRelativeLocation( FVector( 160.0f, 0.0f, 140.0f ) );
	
	// this statement doesnt work? 1) delete _BP 2) recompile 3) create new _BP 4) drag it into editor
	AutoPossessPlayer = EAutoReceiveInput::Player0;

}

// Called when the game starts or when spawned
void AWalkingTeapot::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWalkingTeapot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AWalkingTeapot::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// reused code from CO2301 lab2

	PlayerInputComponent->BindAxis( "Drive", this, &AWalkingTeapot::MoveByAmount );
	PlayerInputComponent->BindAxis( "Turn", this, &AWalkingTeapot::RotateByAmount );

}

void AWalkingTeapot::MoveByAmount( float Value ) {

	// reused code from CO2301 lab2

	DeltaLocation = FVector( Value*MoveSpeed*GetWorld()->DeltaTimeSeconds, 0.0f, 0.0f );
	AddActorLocalOffset( DeltaLocation, true );

}

void AWalkingTeapot::RotateByAmount( float Value ) {

	// reused code from CO2301 lab2

	// calc rotation in proper units
	float RotateAmount = Value*RotationSpeed * GetWorld()->DeltaTimeSeconds;
	FRotator Rotation = FRotator( 0.0f, RotateAmount, 0.0f );
	DeltaRotation = FQuat( Rotation );

	// apply
	AddActorLocalRotation( DeltaRotation, true );

}

