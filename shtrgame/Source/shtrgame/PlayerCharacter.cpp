// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// reused code from CO2301 lab2, lab8

	InputComponent->BindAxis( "Drive", this, &APlayerCharacter::DriveEvent );
	InputComponent->BindAxis( "Turn", this, &APlayerCharacter::TurnEvent );
	InputComponent->BindAxis( "Strafe", this, &APlayerCharacter::StrafeEvent );
	InputComponent->BindAxis( "Look", this, &APlayerCharacter::LookEvent );
	
	InputComponent->BindAction( "Fire", IE_Pressed, this, &APlayerCharacter::FireTriggerPullEvent );
	InputComponent->BindAction( "Fire", IE_Released, this, &APlayerCharacter::FireTriggerReleaseEvent );
	
	InputComponent->BindAction( "Dash", IE_Pressed, this, &APlayerCharacter::DashPressEvent );
	InputComponent->BindAction( "Dash", IE_Released, this, &APlayerCharacter::DashReleaseEvent );

}

void APlayerCharacter::DriveEvent( float AxisValue ) {

	// reused code from CO2301 lab2
	
	FRotator Rotation = GetControlRotation(); // Controller->GetControlRotation();
	AddMovementInput( Rotation, MoveSpeed, false );

}

void APlayerCharacter::TurnEvent( float AxisValue ) {

	// reused code from CO2301 lab2

	// calc rotation in proper units
	float RotateAmount = AxisValue*RotationSpeed * GetWorld()->DeltaTimeSeconds;

	// apply
	
	// an actor is standing on some plane
	// i want the actor to rotate sideways parallel to this plane
	PawnOwner->AddActorLocalRotation( FRotator( 0.0f, RotateAmount, 0.0f ) );

	// useless anyway
	//PawnOwner->AddControllerYawInput( RotateAmount );

}

void APlayerCharacter::LookEvent( float AxisValue ) {

	// help:
	// https://cpp.hotexamples.com/examples/-/-/AddControllerYawInput/cpp-addcontrolleryawinput-function-examples.html
	
	// calc rotation in proper units
	float RotateAmount = AxisValue*RotationSpeed * GetWorld()->DeltaTimeSeconds;

	//ConstrainDirectionToPlane // how???

	// apply
	
	// with current settings it doesn't work
	//PawnOwner->AddControllerPitchInput( RotateAmount );

}

void APlayerCharacter::StrafeEvent( float AxisValue ) {

	FVector DeltaLocation = FVector( 0.0f, AxisValue*MoveSpeed*GetWorld()->DeltaTimeSeconds, 0.0f );
	GetOwner()->AddActorLocalOffset( DeltaLocation, true );

}

void APlayerCharacter::FireTriggerPullEvent( FVector CameraLocation, FRotator CameraRotation ) {

	// help:
	// https://www.orfeasel.com/single-line-raycasting/
	// https://cpp.hotexamples.com/examples/-/-/GetActorEyesViewPoint/cpp-getactoreyesviewpoint-function-examples.html
	// https://forums.unrealengine.com/t/how-to-get-active-camera-object/331893/4

	//--------------------------------+++
	// Definitions.
	
    FHitResult HitResult;
	FVector StartLocation, EndLocation;
	FVector CamSightLineEnd;
	FRotator SecondCameraRotation;

	float RayLength;

	FCollisionQueryParams CollisionParameters;

	//--------------------------------+++
	// Actual code.
	
    RayLength = 2000;

	// i pretend i want to draw a line between camera and something far away at the
	// center of the screen - i start at CameraLocation and arrive at CamSightLineEnd
	SecondCameraRotation = FRotator( CameraRotation.Pitch, CameraRotation.Yaw, CameraRotation.Roll );
	CamSightLineEnd = CameraLocation + ( SecondCameraRotation.Vector() )*RayLength;

	// but actually i want to draw a line between
	StartLocation = CameraLocation;
    EndLocation = CamSightLineEnd;

    GetOwner()->ActorLineTraceSingle(
		HitResult,
		StartLocation, EndLocation,
		ECollisionChannel::ECC_WorldDynamic, CollisionParameters
		);
 
    // boolean parameter forces lines to be persistent so the raycast is not erased in millisecond
    // last parameter is the width of the lines
    DrawDebugLine( GetWorld(), StartLocation, EndLocation, FColor::Orange, true, -1, 0, 1.0f );

}
void APlayerCharacter::FireTriggerReleaseEvent() {

	// reused code from CO2301 lab

	if(TeabagClass) {
	
		// obtain my custom pawn
		// it has projectile spawn point
		AWalkingTeapot *PawnTeapot = Cast<AWalkingTeapot>( PawnOwner );

		FVector SpawnLocation = PawnTeapot->ProjectileSpawnPointSceneComp->GetComponentLocation();
		FRotator SpawnRotation = PawnTeapot->ProjectileSpawnPointSceneComp->GetComponentRotation();
		ATeabag* TempBag = GetWorld()->SpawnActor<ATeabag>( TeabagClass, SpawnLocation, SpawnRotation );

	}

}

void APlayerCharacter::DashPressEvent() {
	MoveSpeed += DashSpeed;
}
void APlayerCharacter::DashReleaseEvent() {
	MoveSpeed -= DashSpeed;
}