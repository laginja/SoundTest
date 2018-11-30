// Fill out your copyright notice in the Description page of Project Settings.

#include "AreaScanner.h"

#include <Engine/Engine.h>

#include "DrawDebugHelpers.h"
#include "math.h"

// Sets default values for this component's properties
UAreaScanner::UAreaScanner()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAreaScanner::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UAreaScanner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	float DegreesPerSection = 360.f / NumberOfTraces;
	FHitResult FirstHitResult;
	FHitResult SecondHitResult;
	for (int i = 0; i < NumberOfTraces; ++i)
	{
		DrawDebugLine(GetWorld(), GetReachLineStart(), GetReachLineEnd(FRotator(0, i  * DegreesPerSection, 0)), FColor::Green, false, 1, 0, 1);
		if (i < NumberOfTraces - 1)		
		{
			FirstHitResult = GetLineTraceResult(GetReachLineStart(), GetReachLineEnd(FRotator(0, i  * DegreesPerSection, 0)));
			SecondHitResult = GetLineTraceResult(GetReachLineStart(), GetReachLineEnd(FRotator(0, (i + 1)  * DegreesPerSection, 0)));
		}
		else	
		{
			FirstHitResult = GetLineTraceResult(GetReachLineStart(), GetReachLineEnd(FRotator(0, i  * DegreesPerSection, 0)));
			SecondHitResult = GetLineTraceResult(GetReachLineStart(), GetReachLineEnd(FRotator(0, 0, 0)));
		}
		float FirstDistance = FirstHitResult.Distance;
		float SecondDistance = SecondHitResult.Distance;
		float ThirdDistance = (FirstHitResult.ImpactPoint - SecondHitResult.ImpactPoint).Size();
		DrawDebugLine(GetWorld(), FirstHitResult.ImpactPoint, SecondHitResult.ImpactPoint, FColor::Red, false, 1, 0, 4);
		RoomArea += CalculateTriangleArea(FirstDistance, SecondDistance, ThirdDistance);
	}
	UE_LOG(LogTemp, Warning, TEXT("Room area: %f"), RoomArea);
	RoomArea = 0;
}

const FHitResult UAreaScanner::GetLineTraceResult(FVector Start, FVector End)
{
	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams);

	return HitResult;
}

FVector UAreaScanner::GetReachLineStart()
{
	FVector PlayerEyesLocation;
	FRotator PlayerEyesRotation;
	GetWorld()->GetFirstPlayerController()->GetActorEyesViewPoint(PlayerEyesLocation, PlayerEyesRotation);

	return PlayerEyesLocation;
}

FVector UAreaScanner::GetReachLineEnd(FRotator Rotator)
{
	FVector PlayerEyesLocation;
	FRotator PlayerEyesRotation;
	auto PlayerCharacter = GetWorld()->GetFirstPlayerController()->GetPawn();
	FRotator TargetRotation = PlayerCharacter->GetActorRotation();
	FRotator Rotated = FRotator(0, TargetRotation.Yaw + Rotator.Yaw, 0);
	GetWorld()->GetFirstPlayerController()->GetActorEyesViewPoint(PlayerEyesLocation, PlayerEyesRotation);

	return PlayerEyesLocation + Rotated.Vector() * Reach;
}



FVector UAreaScanner::GetLeftReachLineEnd()
{
	FVector PlayerEyesLocation;
	FRotator PlayerEyesRotation;
	auto PlayerCharacter = GetWorld()->GetFirstPlayerController()->GetPawn();

	FRotator TargetRotation = PlayerCharacter->GetActorRotation();
	// Rotiraj lijevo za 45 stupnjeva
	FRotator Rotated = FRotator(0, TargetRotation.Yaw - 45, 0);
	GetWorld()->GetFirstPlayerController()->GetActorEyesViewPoint(PlayerEyesLocation, PlayerEyesRotation);

	return PlayerEyesLocation + Rotated.Vector() * Reach;
}

FVector UAreaScanner::GetRightReachLineEnd()
{
	FVector PlayerEyesLocation;
	FRotator PlayerEyesRotation;
	auto PlayerCharacter = GetWorld()->GetFirstPlayerController()->GetPawn();

	FRotator TargetRotation = PlayerCharacter->GetActorRotation();
	// Rotiraj desno za 45 stupnjeva
	FRotator Rotated = FRotator(0, TargetRotation.Yaw + 45, 0);
	GetWorld()->GetFirstPlayerController()->GetActorEyesViewPoint(PlayerEyesLocation, PlayerEyesRotation);

	return PlayerEyesLocation + Rotated.Vector() * Reach;
}

float UAreaScanner::CalculateTriangleArea(float a, float b, float c)
{
	float p = (a + b + c) / 2;

	return sqrt(p*(p-a)*(p-b)*(p-c));
}

