// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldPosition.h"
#include "GameFramework/Actor.h"
#include "Building_Escape.h"



// Sets default values for this component's properties
UWorldPosition::UWorldPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();
	
	FString ObjectName = GetOwner()->GetName();
	FString ObjectPosition = GetOwner()->GetActorLocation().ToString();

	// Using c++17 structured binding to access x,y,z via reference ; No Copies
	FVector Position = GetOwner()->GetActorLocation();
	auto& [x, y, z] = Position;

	//UE_LOG(LogTemp, Warning, TEXT("Actor Component Name: %s"), *GetNameSafe(this));
	UE_LOG(LogBuildng_Escape, Warning, TEXT("Object Name: %s Coordinates; %s"), *ObjectName, *ObjectPosition);
	UE_LOG(LogBuildng_Escape, Error, TEXT("C++17 VERSION: Object Name: %s Coordinates; %0.2f, %0.2f, %0.2f"), *ObjectName, x, y, z);
}

// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

