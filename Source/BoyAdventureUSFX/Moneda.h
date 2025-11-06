// Fill out your copyright notice in the Description page of Project Settings.

/* Implemente la clase moneda, que tendrá la  posibilidad de rotar en un determinado eje, una vez que llega a un ciclo, su sentido de rotación cambia en el otro sentido de acuerdo a un limite, incorpore los atributos de  velocidadRotacion y AnguloMaximoRotacion, luego de rotar en ambos sentidos, debe realizar un salto aleatorio a otro lugar que se encuentre vacío.*/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Moneda.generated.h"

class UStataticMeshComponent;

UCLASS()
class BOYADVENTUREUSFX_API AMoneda : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMoneda();

public:
	//float velocidadRotacion = 10.0f;
	//float anguloMaximoRotacion = 359.0f;

	//void RotarMoneda(float DeltaTime);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UStaticMeshComponent* MallaComponenteMoneda;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	
};
