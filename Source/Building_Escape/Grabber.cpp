// Copyrights Salim Pamukcu 2020

#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandle();
	SetupInputComponent();
}

void UGrabber::FindPhysicsHandle()
{
	// Check for Physics Component
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{
		// Physics Handles Component Exists; used for safe guard of pointers
	}
	else
	{
		UE_LOG(LogBuildng_Escape, Error, TEXT("No Physics Handle Component Found on %s"), *GetOwner()->GetName());
	}
}

void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
}


void UGrabber::Grab()
{
	UE_LOG(LogBuildng_Escape, Warning, TEXT("Grabber pressed!"));
	
	// TODO: raycast only when key is pressed & check if we reach any actor with Physics Handle collision channel set
	auto HitResult=GetFirstPhysicsBodyInReach();
	
	// TODO: Attach Physics Handle;if we hit something then attach Physics Handle
	//PhysicsHandle->GrabComponentAtLocation(HitResult.GetComponent(), HitResult.BoneName, HitResult.Location );
	//auto NewLocation = PhysicsHandle->CurrentTransform;
	//PhysicsHandle->SetTargetLocation(NewLocation.GetLocation());
}

void UGrabber::Release()
{
	UE_LOG(LogBuildng_Escape, Warning, TEXT("Grabber released!"));

	//TODO: Remove Physics Handle
	PhysicsHandle->ReleaseComponent();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// If the physics handle is attached
	// Move the the object we are holding

	// Draw a Debugline; NOT NEEDED FOR Actual Game Play
	//DrawDebugLine(GetWorld(), PlayerViewPointLocation, LineTraceEnd, FColor::Green, false, -1.0f, 0, 5.0f);
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	// Get Players Viewpoint to record the Location, Rotation
	FVector PlayerViewPointLocation;
	FRotator  PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	// Ray cast out to a certain distance by LineTraceForObject ; alternative is LineTraceByChannel
	// can be done via Blueprint as well
	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	if (Hit.GetActor())
	{
		UE_LOG(LogBuildng_Escape, Warning, TEXT("Ray Tracing Hit Object Name: %s"), *Hit.GetActor()->GetName());
	}

	return Hit;
}



