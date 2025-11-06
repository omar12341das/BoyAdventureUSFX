// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BoyAdventureUSFXGameMode.generated.h"

class AObstaculo;
class AObstaculoPared;
class AParedMetal;
class ATrampaSierra;
class APlataforma;
class ABoyAdventureUSFXCharacter;
class AMoneda;

UCLASS(minimalapi)
class ABoyAdventureUSFXGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABoyAdventureUSFXGameMode();

	void MoverActorAleatoriamente();

	TArray<AObstaculo*> aObstaculos;

public:
	virtual void BeginPlay() override;

	void CrearObstaculos();

	float direccionRotacion = 1.0f;

	void rotarMoneda();

	APlataforma* Plataforma01;
private:
	AObstaculoPared* Obstaculo;
	AParedMetal* ParedMetal01;

	ATrampaSierra* ts01;
	ATrampaSierra* ts02;



	ABoyAdventureUSFXCharacter* PawnPrincipal;
	AMoneda* moneda01;

private:
	FTimerHandle MovimientoTimer;
	/*FTimerHandle EliminarComponentePlataformaTimer;*/
	FTimerHandle MoverComponentePlataformaTimer;
	/*FTimerHandle MovimientoAleatorioTimer;*/
	FTimerHandle MovimientoComponentesPlataformaTimer;

	FTimerHandle rotarMonedaTimer;

	UPROPERTY(EditAnywhere, Category = "Movimiento")
	float Intervalo = 4.0f;

	UPROPERTY(EditAnywhere, Category = "Movimiento")
	FVector RangoMovimiento = FVector(500.0f, 500.0f, 0.0f); // Solo X e Y

public:
	//void EliminarComponentePlataforma();
	void MoverComponentePlataforma();
};



