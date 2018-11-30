// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AreaScanner.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SOUND_API UAreaScanner : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAreaScanner();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// koliko daleko ce raytraceat (u cm)
	UPROPERTY(EditAnywhere)
	float Reach = 2000.f;

	UPROPERTY(EditAnywhere)
	int NumberOfTraces = 8;

	// area around a character
	float RoomArea = 0;

	// vrati prvi fizicki objekt koji pogodi
	const FHitResult GetLineTraceResult(FVector Start, FVector End);

	FVector GetReachLineStart();
	FVector GetReachLineEnd(FRotator Rotator);

	FVector GetLeftReachLineEnd();
	FVector GetRightReachLineEnd();

	// izracunaj povrsinu trokuta
	float CalculateTriangleArea(float a, float b, float c);
};
