// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void OpenDoor();
	void CloseDoor();
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	

private:
	UPROPERTY(EditAnyWhere)
	float OpenAngle = -90.0f;

	UPROPERTY(EditAnyWhere)
	ATriggerVolume* PressurePlate;
	
	UPROPERTY(EditAnyWhere)
	float DoorCloseDelay = 0.6f;

	float LastDoorOpenTime;

	AActor* Owner; // The owing door

	// Return total mass in kg
	float GetTotalMassOfActorsOnPlate();
	
};
