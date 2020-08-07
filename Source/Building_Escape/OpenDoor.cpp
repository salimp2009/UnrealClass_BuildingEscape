// Copyrights Salim Pamukcu 2020
#define print(text) if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, text)

#include "OpenDoor.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>
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
	print(FString::Printf(TEXT("Door Name: %s, Initial Yaw: %0.2f, TargetYaw: %0.2f"), *ObjectName, InitialYaw, TargetYaw));
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// Logging and On Screen Messages
	GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Blue, FString::Printf(TEXT("Initial Yaw: %0.2f, TargetYaw: %0.2f"), InitialYaw, TargetYaw));
	UE_LOG(LogBuildng_Escape, Warning, TEXT("Door Yaw is %0.2f"), GetOwner()->GetActorRotation().Yaw);
	
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	CurrentYaw = FMath::FInterpTo(CurrentYaw, TargetYaw, DeltaTime, 2.0f); 
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
	
	// Screen Message Update
	GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Orange, FString::Printf(TEXT("Current Yaw: %0.2f"), CurrentYaw));

	// TODO: Learn how to use this
	//GetOwner()->SetActorRelativeRotation(DoorRotation);
	//GetOwner()->AddActorWorldRotation({ 0.0f, CurrentYaw, 0.0f });   // Opens door too fast ; NOT CORRECT ???
}

