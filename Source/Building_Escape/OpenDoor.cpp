// Copyrights Salim Pamukcu 2020
//#define print(Color, text, ...) if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.0f, Color, FString::Printf(text, __VA_ARGS__))
//#define printTC(Color, text, ...) if(GEngine) GEngine->AddOnScreenDebugMessage(-1, DeltaTime, Color, FString::Printf(text, __VA_ARGS__))


//#include "EngineGlobals.h"
//#include "Runtime/Engine/Classes/Engine/Engine.h"

#define OUT

#include "OpenDoor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Actor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	OpenAngle += InitialYaw;

	if (!PressurePlate)
	{
		UE_LOG(LogBuildng_Escape, Error, TEXT("PressurePlate Pointer Not Initialized: %s"), *GetOwner()->GetName());
	}

	ActorThatOpens=GetWorld()->GetFirstPlayerController()->GetPawn();
	
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (TotalMassOfActors()>MassToOpenDoor)
	{
		OpenDoor(DeltaTime);
		DoorLastOpened= GetWorld()->GetTimeSeconds();
	}
	else
	{
		if (GetWorld()->GetTimeSeconds() - DoorLastOpened > DoorCloseDelay)
		{
			 CloseDoor(DeltaTime);
		}
	}
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	CurrentYaw = FMath::FInterpTo(CurrentYaw, OpenAngle, DeltaTime, DoorOpenSpeed);
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);

	//if (ActorThatOpens)
		//printTC(FColor::Green, TEXT("Actor Opens Door: %s"), *ActorThatOpens->GetName());
		//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Green, FString::Printf(TEXT("Actor Opens Door: %s"), *ActorThatOpens->GetName()));
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	CurrentYaw = FMath::FInterpTo(CurrentYaw, InitialYaw, DeltaTime, DoorClosedSpeed);
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
}

float UOpenDoor::TotalMassOfActors() const
{
	float TotalMass = 0.0f;
	
	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	for (AActor* Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogBuildng_Escape, Warning, TEXT("Actor in Pressure Plate: %s, Total Mass: %0.2f"), *Actor->GetName(), TotalMass);
	}
		
	return TotalMass;
}

