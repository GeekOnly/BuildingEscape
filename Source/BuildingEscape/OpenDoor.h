// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Engine.h>
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpenRequest);

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


	void DoorClose();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/*UPROPERTY(BlueprintAssignable)
	FOnOpenRequest onOpenRequest;*/

private:
	UPROPERTY(VisibleAnywhere)
		float OpenAngle = 90.f;	
	
	UPROPERTY(EditAnywhere)
<<<<<<< HEAD
		ATriggerVolume* PressurePlate = nullptr ;
=======
		ATriggerVolume* PressurePlate;
>>>>>>> parent of 00068ec... 89 Pointer
	
	AActor* ActorThatOpens = nullptr; // Remamber pawn

	//The owing door
	AActor* Owner = nullptr;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 1.f;

	float LastDoorOpenTime;
};
