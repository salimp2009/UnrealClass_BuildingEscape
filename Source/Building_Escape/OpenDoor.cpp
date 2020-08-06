// Copyrights Salim Pamukcu 2020


#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Building_Escape.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	InitialYaw= GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	TargetYaw += InitialYaw;

	// Alternative Ways to Debug
	FString ObjectName = GetOwner()->GetName();
	UE_LOG(LogBuildng_Escape, Warning, TEXT("Door Name: %s, Door Yawn is %0.2f"),*ObjectName, InitialYaw);	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	UE_LOG(LogBuildng_Escape, Warning, TEXT("Door Yaw is %0.2f"), GetOwner()->GetActorRotation().Yaw);
	//UE_LOG(LogBuildng_Escape, Error, TEXT("Door Rotation is %s"), *GetOwner()->GetActorRotation().ToString());
	
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	CurrentYaw = FMath::FInterpTo(CurrentYaw, TargetYaw, DeltaTime, 2.0f); 
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
	
	//GetOwner()->AddActorWorldRotation({ 0.0f, CurrentYaw, 0.0f });   // Opens door too fast ; NOT CORRECT ???

}

