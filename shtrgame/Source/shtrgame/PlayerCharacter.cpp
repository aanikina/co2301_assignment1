// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlayerCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// initialize components

	CameraComp = CreateDefaultSubobject<UCameraComponent>( TEXT("CameraComponent") );
	CameraSpringArmComp = CreateDefaultSubobject<USpringArmComponent>( TEXT("CameraSpringArmComponent") );

	// build component hierarchy

	CameraSpringArmComp->SetupAttachment( RootComponent );
	CameraComp->SetupAttachment( CameraSpringArmComp, USpringArmComponent::SocketName );

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
	// help:
	// https://youtu.be/xZjZimU31wc
	
	PlayerInputComponent->BindAxis( TEXT("Drive"), this, &APlayerCharacter::DriveEvent );
	//PlayerInputComponent->BindAxis( TEXT("Turn"), this, &APlayerCharacter::TurnEvent );
	PlayerInputComponent->BindAxis( TEXT("Turn"), this, &APlayerCharacter::AddControllerYawInput );
	PlayerInputComponent->BindAxis( TEXT("Strafe"), this, &APlayerCharacter::StrafeEvent );
	//PlayerInputComponent->BindAxis( TEXT("Look"), this, &APlayerCharacter::LookEvent );
	PlayerInputComponent->BindAxis( TEXT("Look"), this, &APlayerCharacter::AddControllerPitchInput );
	
	//PlayerInputComponent->BindAction( TEXT("Fire"), IE_Pressed, this, &APlayerCharacter::FireTriggerPullEvent );
	//PlayerInputComponent->BindAction( TEXT("Fire"), IE_Released, this, &APlayerCharacter::FireTriggerReleaseEvent );
	
	PlayerInputComponent->BindAction( TEXT("Dash"), IE_Pressed, this, &APlayerCharacter::DashPressEvent );
	PlayerInputComponent->BindAction( TEXT("Dash"), IE_Released, this, &APlayerCharacter::DashReleaseEvent );
	
	PlayerInputComponent->BindAction( TEXT("Jump"), IE_Pressed, this, &APlayerCharacter::JumpPressEvent );
	PlayerInputComponent->BindAction( TEXT("Jump"), IE_Released, this, &APlayerCharacter::JumpReleaseEvent );

}

void APlayerCharacter::DriveEvent( float AxisValue ) {

	// reused code from CO2301 lab2
	
	AddMovementInput( GetActorForwardVector()*AxisValue, MoveSpeed, false );

}

/*
void APlayerCharacter::TurnEvent( float AxisValue ) {

	// reused code from CO2301 lab2
	
	UE_LOG( LogTemp, Warning, TEXT("TurnEvent") );

	// calc rotation in proper units
	float RotateAmount = AxisValue*RotationSpeed * GetWorld()->DeltaTimeSeconds;

	// apply

	AddControllerYawInput( RotateAmount );

}*/

/*
void APlayerCharacter::LookEvent( float AxisValue ) {

	// help:
	// https://cpp.hotexamples.com/examples/-/-/AddControllerYawInput/cpp-addcontrolleryawinput-function-examples.html
	
	UE_LOG( LogTemp, Warning, TEXT("LookEvent") );
	
	// calc rotation in proper units
	float RotateAmount = AxisValue*RotationSpeed * GetWorld()->DeltaTimeSeconds;

	// apply
	AddControllerPitchInput( RotateAmount );

}*/

void APlayerCharacter::StrafeEvent( float AxisValue ) {

	//FVector DeltaLocation = FVector( 0.0f, AxisValue*MoveSpeed*GetWorld()->DeltaTimeSeconds, 0.0f );
	//AddActorLocalOffset( DeltaLocation, true );

	AddMovementInput( GetActorRightVector()*AxisValue*MoveSpeed, 1.0f, false );

}

void APlayerCharacter::FireTriggerPullEvent( FVector CameraLocation, FRotator CameraRotation ) {
	
	UE_LOG( LogTemp, Warning, TEXT("FireTriggerPullEvent") );

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
    //DrawDebugLine( GetWorld(), StartLocation, EndLocation, FColor::Orange, true, -1, 0, 1.0f );

}
void APlayerCharacter::FireTriggerReleaseEvent() {
	
	UE_LOG( LogTemp, Warning, TEXT("FireTriggerReleaseEvent") );

	// reused code from CO2301 lab

	/*
	if(TeabagClass) {
	
		// obtain my custom pawn
		// it has projectile spawn point
		AWalkingTeapot *PawnTeapot = Cast<AWalkingTeapot>( PawnOwner );

		FVector SpawnLocation = PawnTeapot->ProjectileSpawnPointSceneComp->GetComponentLocation();
		FRotator SpawnRotation = PawnTeapot->ProjectileSpawnPointSceneComp->GetComponentRotation();
		ATeabag* TempBag = GetWorld()->SpawnActor<ATeabag>( TeabagClass, SpawnLocation, SpawnRotation );

	}
	*/

}

void APlayerCharacter::DashPressEvent() {
	UE_LOG( LogTemp, Warning, TEXT("DashPressEvent") );
	MoveSpeed += DashSpeed;
}
void APlayerCharacter::DashReleaseEvent() {
	UE_LOG( LogTemp, Warning, TEXT("DashReleaseEvent") );
	MoveSpeed -= DashSpeed;
}

void APlayerCharacter::JumpPressEvent() {
	
	// call already implemented jump function
	Jump();

}
void APlayerCharacter::JumpReleaseEvent() {

	UE_LOG( LogTemp, Warning, TEXT("JumpReleaseEvent") );
	
}