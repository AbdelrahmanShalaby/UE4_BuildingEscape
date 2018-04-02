// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"

#define OUT
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
	Owner = GetOwner();
	if (PressurePlate == nullptr)
	{
		//Missing input component
		UE_LOG(LogTemp, Error, TEXT("Missing Pressure Plate"));
	}
}



void UOpenDoor::CloseDoor()
{
	
	//Set the door rotation
	//Owner->SetActorRotation(FRotator(0.f, 0.f, 0.f));
	OnClose.Broadcast();
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// poll the Trigger Volume
	// If the ActorThatOpens is the volume
	if (GetTotalMassOfActorsOnPlate() > TriggerMass)
	{
		OnOpen.Broadcast();
	}
	else
	{
		CloseDoor();
	}
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.f;
	TArray<AActor*>OverlappingActors;
	if (PressurePlate == nullptr) { return TotalMass; }
	// Find all the overlapping actors
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	// iterate through them and adding their masses
	for (const auto& Actor  : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("%s"),*Actor->GetName());
	}
	return TotalMass;
}