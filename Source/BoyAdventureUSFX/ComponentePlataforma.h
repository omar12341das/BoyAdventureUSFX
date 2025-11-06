// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ComponentePlataforma.generated.h"

UCLASS()
class BOYADVENTUREUSFX_API AComponentePlataforma : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AComponentePlataforma();

public:
	FVector DestinoMovimiento;
	float DesplazamientoPZ;
	float DesplazamientoNZ;
	float DesplazamientoPX;
	float DesplazamientoNX;
	float DesplazamientoPY;
	float DesplazamientoNY;
	bool bMovimiento;
	FVector PosicionInicial;
	float IncrementoX;

	void Moverse();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UStaticMeshComponent* MallaComponentePlataforma;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
