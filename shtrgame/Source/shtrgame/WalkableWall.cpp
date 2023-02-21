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

	// don't need this
	CollisionBoxComp->OnComponentEndOverlap.AddDynamic( this, &AWalkableWall::OnCollisionBoxOverlapEnd );

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
	if( OtherActor->GetInstigatorController() ) {
		return;
	}

	// obtain my custom player controller
	// that is capable of remembering walls
	ACustomPlayerController *PlayerController = Cast<ACustomPlayerController>( OtherActor->GetInstigatorController() );

	if( PlayerController->LastUsedWall == this ) {
		// i already collided with this wall, not doing anything
		return;
	}

	// i have not collided with this wall yet
	
	// if i stand between several walls, this collision
	// will keep firing, so the pawn will rotate chaotically
	// in order to avoid it, remember and check time difference
	// help:
	// https://docs.unrealengine.com/4.27/en-US/BlueprintAPI/Utilities/Time/
	// https://www.reddit.com/r/unrealengine/comments/bmqpoo/how_to_make_an_acurate_level_timer_0000000/

	float LastUsedWallSeconds = UGameplayStatics::GetRealTimeSeconds( GetWorld() );

	// compare it
	if( LastUsedWallSeconds - PlayerController->LastUsedWallSeconds < PlayerController->DelayBetweenWallCollisionSnapping ) {
		// this collision was triggered too fast, most likely
		// im standing in a corner
		// not doing anything
		return;
	}

	// now i can actually proceed
	
	UE_LOG( LogTemp, Log, TEXT("Player's LastUsedWall updated") );

	// detach from previous wall
	FDetachmentTransformRules DetachmentRules(
		EDetachmentRule::KeepWorld, // location
		EDetachmentRule::KeepRelative, // rotation
		EDetachmentRule::KeepWorld, // scale
		true
		);
	OtherActor->DetachFromActor( DetachmentRules );

	// remember this wall
	PlayerController->LastUsedWall = this;
	
	// remember current time
	PlayerController->LastUsedWallSeconds = LastUsedWallSeconds;

	// snap player to this wall
	// help:
	// https://stackoverflow.com/questions/72888511/how-to-log-fvector-in-unreal-engine
	// https://forums.unrealengine.com/t/how-to-attach-an-actor-to-any-surface/467663/4
	// https://docs.unrealengine.com/4.27/en-US/API/Runtime/Engine/GameFramework/AActor/AttachToComponent/
	// https://forums.unrealengine.com/t/how-to-attach-components-maintaining-their-orientation/86433
	// https://d3kjluh73b9h9o.cloudfront.net/original/4X/d/c/7/dc762b96412ad0fe08ca6c9fa8c8f67047ed6629.jpeg

	FAttachmentTransformRules AttachmentRules(
		EAttachmentRule::KeepWorld, // location
		EAttachmentRule::KeepRelative, // rotation
		EAttachmentRule::KeepWorld, // scale
		true
		);

	OtherActor->AttachToActor(
		this,
		AttachmentRules
		);

}

void AWalkableWall::OnCollisionBoxOverlapEnd(
	UPrimitiveComponent *OverlappedComp,
	AActor *OtherActor,
	UPrimitiveComponent *OtherComp,
	int32 OtherBodyIndex
) {

	// make sure i collided with an actor that is being controlled
	if( OtherActor->GetInstigatorController() ) {
		return;
	}

	// obtain my custom player controller
	// that is capable of remembering walls
	ACustomPlayerController *PlayerController = Cast<ACustomPlayerController>( OtherActor->GetInstigatorController() );

	if( PlayerController->LastUsedWall != this ) {
		// i have collided with some other wall, no need to do anything here
		return;
	}

	// i stopped colliding with this wall
	// whenever pawn moves within the collision box, this event is triggered
	// along with OnCollisionBoxOverlapBegin,
	// so i want to check time - is OnCollisionBoxOverlapBegin happened too soon,
	// then my pawn is not hanging in thin air
	// and should not fall on the floor
	
	float LastUsedWallSeconds = UGameplayStatics::GetRealTimeSeconds( GetWorld() );

	if( LastUsedWallSeconds - PlayerController->LastUsedWallSeconds < PlayerController->DelayBetweenWallCollisionSnapping ) {
		// this collision was triggered too fast, most likely
		// im moving across this wall
		// not doing anything
		return;
	}
	
	// now i can actually proceed
	
	UE_LOG( LogTemp, Log, TEXT("Player is not using any walls") );


	/*
	// i stopped colliding with this wall, but i have not collided with any
	// ither wall yet - my pawn is hanging in the air
	
	UE_LOG( LogTemp, Log, TEXT("Player is not using any walls") );
	
	// reset last used wall so that i can use this wall again
	PlayerController->LastUsedWall = nullptr;

	// detach the player from this wall

	FDetachmentTransformRules rules(
		EDetachmentRule::KeepWorld, // location
		EDetachmentRule::KeepRelative, // rotation
		EDetachmentRule::KeepWorld, // scale
		true
		);

	OtherActor->DetachFromActor(
		rules
		);

	*/

}