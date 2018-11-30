// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RayTracer.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SOUND_API URayTracer : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URayTracer();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	float GetFrontDelay();

	UFUNCTION(BlueprintCallable)
	float GetRearDelay();

	UFUNCTION(BlueprintCallable)
	float GetLeftDelay();

	UFUNCTION(BlueprintCallable)
	float GetRightDelay();

private:
	// koliko daleko ce raytraceat (u cm)
	UPROPERTY(EditAnywhere)
	float Reach = 2000.f;
	
	// vrati prvi fizicki objekt koji pogodi
	const FHitResult GetLineTraceResult(FVector Start, FVector End);

	FVector GetReachLineStart();

	FVector GetReachLineEnd(FRotator Rotator);
	FVector GetReachDimensionsLineEnd(FRotator Rotator);

	float SpeedOfSound = 343.f;

	float FrontDelay = 1.f;
	float RearDelay = 1.f;
	float LeftDelay = 1.f;
	float RightDelay = 1.f;
	float UpDelay = 1.f;
	float DownDelay = 1.f;

	float RoomHeight = 0;
	float RoomWidth = 0;
	float RoomLength = 0;
};
