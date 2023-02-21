// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerWall.h"

ATriggerWall::ATriggerWall() {

	// reused code from WalkableWall actor
	
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = false; // dont need tick
	
	// initialize components
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>( TEXT("StaticMeshComponent") );
	
	// build component hierarchy
	SetRootComponent( StaticMeshComp );

}

void ATriggerWall::BeginPlay() {

	Super::BeginPlay();
	
	// help:
	// https://forums.unrealengine.com/t/how-to-use-onactorbeginoverlap-c-code/82889/10
	// whenever using signature provided on the link, got error that prohibited
	// naming the first argument "Owner";
	// with different signature got this error:
	/*
	void TSparseDynamicDelegate <FActorBeginOverlapSignature_MCSignature,AActor,FActorBeginOverlapSignatureInfoGetter>::
		__Internal_AddDynamic<ATriggerWall>(
		UserClass *,
		void (__cdecl ATriggerWall::* )(AActor *,AActor *),
		FName)
		':
			cannot convert argument 2 from '
				void (__cdecl ATriggerWall::* )(AActor *)
				'
			to '
				void (__cdecl ATriggerWall::* )(AActor *,AActor *)
			'
	*/
	// https://www.youtube.com/watch?v=H2I7I8blgn8
    OnActorBeginOverlap.AddDynamic( this, &ATriggerWall::OnOverlapBegin );

	// again got this error:
	/*
	void TSparseDynamicDelegate<FActorEndOverlapSignature_MCSignature,AActor,FActorEndOverlapSignatureInfoGetter>::
	__Internal_AddDynamic<ATriggerWall>(
		UserClass *,
		void (__cdecl ATriggerWall::* )(
			AActor *,AActor *
			),
		FName
		)':
			cannot convert argument 2 from '
			void (__cdecl ATriggerWall::* )(
				UPrimitiveComponent *,AActor *,UPrimitiveComponent *,int32
				)'
			to 'void (__cdecl ATriggerWall::* )(AActor *,AActor *)'

	*/
    OnActorEndOverlap.AddDynamic( this, &ATriggerWall::OnOverlapEnd );

	}

//void ATriggerWall::OnOverlapBegin( UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult ) {
void ATriggerWall::OnOverlapBegin( AActor *OverlappedActor, AActor *OtherActor ) {

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

	// i have not collided with this wall yet
	
	// if i stand between several walls, this collision
	// will keep firing, so the pawn will rotate chaotically
	// in order to avoid it, remember and check time difference
	// help:
	// https://docs.unrealengine.com/4.27/en-US/BlueprintAPI/Utilities/Time/
	// https://www.reddit.com/r/unrealengine/comments/bmqpoo/how_to_make_an_acurate_level_timer_0000000/

	float LastUsedWallSeconds = UGameplayStatics::GetRealTimeSeconds( GetWorld() );

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

//void ATriggerWall::OnOverlapEnd( UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex ) {
void ATriggerWall::OnOverlapEnd( AActor *OverlappedActor, AActor *OtherActor ) {

	// make sure i collided with an actor that is being controlled
	if( OtherActor->GetInstigatorController() == nullptr ) {
		return;
	}

	// obtain my custom player controller
	// that is capable of remembering walls
	ACustomPlayerController *PlayerController = Cast<ACustomPlayerController>( OtherActor->GetInstigatorController() );

	if( PlayerController->LastUsedWall != this ) {
		// i have collided with some other wall, no need to do anything here
		return;
	}
	PlayerController->LastUsedWall = nullptr;

	// i stopped colliding with this wall
	// if i set physics enabled on my pawn then
	// whenever pawn moves within the collision box, this event is triggered
	// along with OnCollisionBoxOverlapBegin,
	// i disabled physics but anyway want to check time - is OnCollisionBoxOverlapBegin happened too soon,
	// then my pawn is ???
	
	float LastUsedWallSeconds = UGameplayStatics::GetRealTimeSeconds( GetWorld() );

	if( LastUsedWallSeconds - PlayerController->LastUsedWallSeconds < PlayerController->DelayBetweenWallCollisionSnapping ) {
		// this collision was triggered too fast
		return;
	}
	
	// now i can actually proceed

	UE_LOG( LogTemp, Log, TEXT("Player is not using any walls") );
	
	// detach from previous wall
	FDetachmentTransformRules DetachmentRules(
		EDetachmentRule::KeepWorld, // location
		EDetachmentRule::KeepRelative, // rotation
		EDetachmentRule::KeepWorld, // scale
		false
		);
	OtherActor->DetachFromActor( DetachmentRules );

}
