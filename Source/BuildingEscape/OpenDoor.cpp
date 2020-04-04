// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"

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
<<<<<<< HEAD
	//ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
=======

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
>>>>>>> parent of 00068ec... 89 Pointer
	Owner = GetOwner();
	if (!PressurePlate) 
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing pressure plate "), *GetOwner()->GetName())
	}
}

void UOpenDoor::OpenDoor()
{
		//Owner->SetActorRotation(FRotator(0.f,OpenAngle, 0.f));
	//onOpenRequest.Broadcast();
}

void UOpenDoor::DoorClose()
{
	Owner->SetActorRotation(FRotator(0.f, 0.0, 0.f));
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Poll the Trigger Volume
	if (PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp,Warning,TEXT("OpenDoor"));
	}

	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay) {
		DoorClose();
	}
}

<<<<<<< HEAD
float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.f;

	//Find all the overlapping actor
	TArray<AActor*> OverlappingActor;
	PressurePlate->GetOverlappingActors(OUT OverlappingActor);

	//if (!PressurePlate){return TotalMass;}
	//Iterate through them adding thier masses
	for (const auto& Actor : OverlappingActor)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp,Warning,TEXT("%s on pressure plate"),*Actor->GetName())
	}

	return TotalMass;
}

=======
>>>>>>> parent of 00068ec... 89 Pointer
