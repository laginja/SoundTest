// Fill out your copyright notice in the Description page of Project Settings.

#include "RayTracer.h"

#include <Engine/Engine.h>
#include "DrawDebugHelpers.h"


// Sets default values for this component's properties
URayTracer::URayTracer()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URayTracer::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("RayTracer online"));
	
}


// Called every frame
void URayTracer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	DrawDebugLine(GetWorld(), GetReachLineStart(), GetReachLineEnd(FRotator(0, 0, 0)), FColor::Green, false, 1, 0, 1);
	DrawDebugLine(GetWorld(), GetReachLineStart(), GetReachLineEnd(FRotator(0, 180, 0)), FColor::Green, false, 1, 0, 1);
	DrawDebugLine(GetWorld(), GetReachLineStart(), GetReachLineEnd(FRotator(0, 270, 0)), FColor::Blue, false, 1, 0, 1);
	DrawDebugLine(GetWorld(), GetReachLineStart(), GetReachLineEnd(FRotator(0, 90, 0)), FColor::Blue, false, 1, 0, 1);
	DrawDebugLine(GetWorld(), GetReachLineStart(), GetReachLineEnd(FRotator(90, 0, 0)), FColor::Red, false, 1, 0, 1);
	DrawDebugLine(GetWorld(), GetReachLineStart(), GetReachLineEnd(FRotator(-90, 0, 0)), FColor::Red, false, 1, 0, 1);
	

	auto FrontHitResult = GetLineTraceResult(GetReachLineStart(), GetReachLineEnd(FRotator(0, 0, 0)));
	auto RearHitResult = GetLineTraceResult(GetReachLineStart(), GetReachLineEnd(FRotator(0, 180, 0)));
	auto LeftHitResult = GetLineTraceResult(GetReachLineStart(), GetReachLineEnd(FRotator(0, 270, 0)));
	auto RightHitResult = GetLineTraceResult(GetReachLineStart(), GetReachLineEnd(FRotator(0, 90, 0)));
	auto UpHitResult = GetLineTraceResult(GetReachLineStart(), GetReachLineEnd(FRotator(90, 0, 0)));
	auto DownHitResult = GetLineTraceResult(GetReachLineStart(), GetReachLineEnd(FRotator(-90, 0, 0)));

	auto FrontActorHit = FrontHitResult.GetActor();
	auto RearActorHit = RearHitResult.GetActor();
	auto LeftActorHit = LeftHitResult.GetActor();
	auto RightActorHit = RightHitResult.GetActor();
	auto UpActorHit = UpHitResult.GetActor();
	auto DownActorHit = DownHitResult.GetActor();

	if (FrontActorHit)
	{
		float DistanceInMeters = FrontHitResult.Distance / 100;
		// izracunaj vrijeme putovanja zvuka do actora 
		FrontDelay = DistanceInMeters / SpeedOfSound;
		UE_LOG(LogTemp, Warning, TEXT("Front hit delay: %fs"), FrontDelay);

		RoomLength += DistanceInMeters;
	}
	else
	{
		// obzirom da nismo nista pogodili, objekt je predaleko da bi stvorio jeku
		FrontDelay = 1.f;
		UE_LOG(LogTemp, Warning, TEXT("Front hit delay: %fs"), FrontDelay);
	}
	if (RearActorHit)
	{
		float DistanceInMeters = RearHitResult.Distance / 100;
		// izracunaj vrijeme putovanja zvuka do actora 
		RearDelay = DistanceInMeters / SpeedOfSound;
		UE_LOG(LogTemp, Warning, TEXT("Rear hit delay: %fs"), RearDelay);

		RoomLength += DistanceInMeters;
	}
	else
	{
		// obzirom da nismo nista pogodili, objekt je predaleko da bi stvorio jeku
		RearDelay = 1.f;
		UE_LOG(LogTemp, Warning, TEXT("Rear hit delay: %fs"), RearDelay);
	}
	if (LeftActorHit)
	{
		float DistanceInMeters = LeftHitResult.Distance / 100;
		// izracunaj vrijeme putovanja zvuka do actora 
		LeftDelay = DistanceInMeters / SpeedOfSound;
		UE_LOG(LogTemp, Warning, TEXT("Left hit delay: %fs"), LeftDelay);

		RoomWidth += DistanceInMeters;
	}
	else
	{
		// obzirom da nismo nista pogodili, objekt je predaleko da bi stvorio jeku
		LeftDelay = 1.f;
		UE_LOG(LogTemp, Warning, TEXT("Left hit delay: %fs"), LeftDelay);
	}
	if (RightActorHit)
	{
		float DistanceInMeters = RightHitResult.Distance / 100;
		// izracunaj vrijeme putovanja zvuka do actora 
		RightDelay = DistanceInMeters / SpeedOfSound;
		UE_LOG(LogTemp, Warning, TEXT("Right hit delay: %fs"), RightDelay);

		RoomWidth += DistanceInMeters;
	}
	else
	{
		// obzirom da nismo nista pogodili, objekt je predaleko da bi stvorio jeku
		RightDelay = 1.f;
		UE_LOG(LogTemp, Warning, TEXT("Right hit delay: %fs"), RightDelay);
	}
	if (UpActorHit)
	{
		float DistanceInMeters = UpHitResult.Distance / 100;
		// izracunaj vrijeme putovanja zvuka do actora 
		UpDelay = DistanceInMeters / SpeedOfSound;
		UE_LOG(LogTemp, Warning, TEXT("Up hit delay: %fs"), UpDelay);

		RoomHeight += DistanceInMeters;
	}
	else
	{
		// obzirom da nismo nista pogodili, objekt je predaleko da bi stvorio jeku
		UpDelay = 1.f;
		UE_LOG(LogTemp, Warning, TEXT("Up hit delay: %fs"), UpDelay);
	}
	if (DownActorHit)
	{
		float DistanceInMeters = DownHitResult.Distance / 100;
		// izracunaj vrijeme putovanja zvuka do actora 
		DownDelay = DistanceInMeters / SpeedOfSound;
		UE_LOG(LogTemp, Warning, TEXT("Down hit delay: %fs"), DownDelay);

		RoomHeight += DistanceInMeters;
	}
	else
	{
		// obzirom da nismo nista pogodili, objekt je predaleko da bi stvorio jeku
		DownDelay = 1.f;
		UE_LOG(LogTemp, Warning, TEXT("Down hit delay: %fs"), DownDelay);
	}

	UE_LOG(LogTemp, Warning, TEXT("Room Height: %fs"), RoomHeight);
	UE_LOG(LogTemp, Warning, TEXT("Room Width: %fs"), RoomWidth);
	UE_LOG(LogTemp, Warning, TEXT("Room Length: %fs"), RoomLength);

	RoomLength = 0;
	RoomWidth = 0;
	RoomHeight = 0;
}

const FHitResult URayTracer::GetLineTraceResult(FVector Start, FVector End)
{
	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams);
	
	return HitResult;
}

FVector URayTracer::GetReachLineStart()
{
	FVector PlayerEyesLocation;
	FRotator PlayerEyesRotation;
	GetWorld()->GetFirstPlayerController()->GetActorEyesViewPoint(PlayerEyesLocation, PlayerEyesRotation);
	
	return PlayerEyesLocation;
}

FVector URayTracer::GetReachLineEnd(FRotator Rotator)
{
	FVector PlayerEyesLocation;
	FRotator PlayerEyesRotation;
	auto PlayerCharacter = GetWorld()->GetFirstPlayerController()->GetPawn();
	FRotator TargetRotation = PlayerCharacter->GetActorRotation();
	FRotator Rotated = FRotator(Rotator.Pitch, TargetRotation.Yaw + Rotator.Yaw, Rotator.Roll);
	GetWorld()->GetFirstPlayerController()->GetActorEyesViewPoint(PlayerEyesLocation, PlayerEyesRotation);

	return PlayerEyesLocation + Rotated.Vector() * Reach;
}

FVector URayTracer::GetReachDimensionsLineEnd(FRotator Rotator)
{
	FVector PlayerEyesLocation;
	FRotator PlayerEyesRotation;
	auto PlayerCharacter = GetWorld()->GetFirstPlayerController()->GetPawn();

	GetWorld()->GetFirstPlayerController()->GetActorEyesViewPoint(PlayerEyesLocation, PlayerEyesRotation);

	return PlayerEyesLocation + Rotator.Vector() * Reach;
}

float URayTracer::GetFrontDelay()
{
	return FrontDelay;
}

float URayTracer::GetRearDelay()
{
	return RearDelay;
}

float URayTracer::GetLeftDelay()
{
	return LeftDelay;
}

float URayTracer::GetRightDelay()
{
	return RightDelay;
}

