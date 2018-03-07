// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "GameFramework/Actor.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandleComponent();
	SetupInputComponent();
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed"));

	/// LINE TRACE  and see if we reach any actor with physics body collision channel set
	GetFirstPhysicsBodyInReach(); 
	/// If we hit something attach a physics handle
	// TODO attach physics handle
}

void UGrabber::Released()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab released"));

	//TODO release physics handle
}
//Look for attached physics handle
void UGrabber::FindPhysicsHandleComponent()
{
	PhisicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhisicsHandle)
	{
		//physics handle is found 
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s missing physics handle component"), *GetOwner()->GetName());

	}
}
//Look for attached inputcomponent (only appear at run time)
void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{

		UE_LOG(LogTemp, Warning, TEXT("Input component has found"));
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Released);
	}
	else
	{
		//Missing input component
	}
}



// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// If the physics handle is attached 
		// move the  object that we're holding



	
	// ...
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	/// Get player view point 
	FVector PlayerViewPiontLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPiontLocation,
		OUT PlayerViewPointRotation
	);


	FVector LineTraceEnd = PlayerViewPiontLocation + PlayerViewPointRotation.Vector() * Reach;
	/*
	/// Draw a red Trace in world to visualise
	DrawDebugLine(
	GetWorld(),
	PlayerViewPiontLocation,
	LineTraceEnd,
	FColor(255, 0, 0),
	false,
	0.f,
	0.f,
	10.f
	);
	*/
	// setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	/// Line trace (AKA ray-cast) out to reach distance
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPiontLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);
	/// See what we hit
	AActor* ActorHit = Hit.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Line trace hit: %s"), *(ActorHit->GetName()));
	}
	return FHitResult();
}