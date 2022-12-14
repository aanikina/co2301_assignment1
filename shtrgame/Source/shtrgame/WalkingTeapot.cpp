// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "WalkingTeapot.h"
// order is important
#include "CustomPawnMovementComponent.h"

// Sets default values
AWalkingTeapot::AWalkingTeapot()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; // from lab8

	// reused code from CO2301 lab2, lab8
	
	// initialize components
	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>( TEXT("SkeletalMeshComponent") );
	CameraComp = CreateDefaultSubobject<UCameraComponent>( TEXT("CameraComponent") );
	CameraSpringArmComp = CreateDefaultSubobject<USpringArmComponent>( TEXT("CameraSpringArmComponent") );
	ProjectileSpawnPointSceneComp = CreateDefaultSubobject<USceneComponent>( TEXT("ProjectileSpawnPointComponent") );
	CustomPawnMovementComp = CreateDefaultSubobject<UCustomPawnMovementComponent>( TEXT("CustomPawnMovementComponent") );
	
	// build component hierarchy

	SetRootComponent( SkeletalMeshComp );

	CameraSpringArmComp->SetupAttachment( SkeletalMeshComp );
	CameraComp->SetupAttachment( CameraSpringArmComp, USpringArmComponent::SocketName );

	ProjectileSpawnPointSceneComp->SetupAttachment( SkeletalMeshComp );
	ProjectileSpawnPointSceneComp->SetRelativeLocation( FVector( 160.0f, 0.0f, 140.0f ) );
	
	// this statement doesnt work? 1) delete _BP 2) recompile 3) create new _BP 4) drag it into editor
	AutoPossessPlayer = EAutoReceiveInput::Player0;

}
