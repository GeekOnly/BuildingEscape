// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "Grabber.h"

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

	//UE_LOG(LogTemp, Warning, TEXT("Grabber Position Rapper"));

	SetupInputComponent();
	FindPhysicHandleComponent();
	
}

void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Input component found"));
		//Bind the input axis
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing input component"), *GetOwner()->GetName());
	}
}

void UGrabber::FindPhysicHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (InputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Input component found"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing input component"), *GetOwner()->GetName());
	}
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	//Line-trace (AKA ray-cast) out to reach distance
	FHitResult HitResult;
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult,
		GetReachLineStart(),
		GetReachLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
		);
	return HitResult;
}



// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PhysicsHandle) { return; }
		//if the physics handle is attached
	if (PhysicsHandle->GrabbedComponent)
	{
		//Move the object that we're holding
		PhysicsHandle->SetTargetLocation(GetReachLineEnd());
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab Pressed!!"));

	//LINE TRACE and see if we reach any actors with physics body collision channel set
	 auto HitResult = GetFirstPhysicsBodyInReach();
	 auto ComponentToGrab = HitResult.GetComponent();
	 auto ActorHit = HitResult.GetActor();

	//If we hit something then attach a physics handle
	 if (ActorHit) 
	 {
		 if (!PhysicsHandle) { return; }
		 //TODO attach physics handle
		 PhysicsHandle->GrabComponent(
			 ComponentToGrab,
			 NAME_None, 
			 ComponentToGrab->GetOwner()->GetActorLocation(), 
			 true);
	 }
}

void UGrabber::Release()
{
	if (!PhysicsHandle) { return; }
	PhysicsHandle->ReleaseComponent();
}

FVector UGrabber::GetReachLineStart() 
{
	//Get player view point this tick
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
		);

	//Todo log out to test
	//UE_LOG(LogTemp, Warning, TEXT("Location: %s. Position: %s"),*PlayerViewPointLocation.ToString(),*PlayerViewPointRotation.ToString());

	return PlayerViewPointLocation + PlayerViewPointRotation.Vector();
}
FVector UGrabber::GetReachLineEnd()
{
	//Get player view point this tick
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
		);

	//Todo log out to test
	//UE_LOG(LogTemp, Warning, TEXT("Location: %s. Position: %s"),*PlayerViewPointLocation.ToString(),*PlayerViewPointRotation.ToString());

	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
}
