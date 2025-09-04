// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Plataforma.generated.h"

class AComponentePlataforma;

UCLASS()
class BOYADVENTUREUSFX_API APlataforma : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlataforma();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int numeroPisos;
	int numeroComponentesPorPiso;
	float alturaEntrePisos;
	float alturaComponente;
	float anchoComponente;
	float profundidadComponente;
	float separacionComponentes;
	FVector posicionInicial;

	TMap<FVector, AComponentePlataforma*> mComponentesPlataforma;
	TMap<int32, AComponentePlataforma*> mComponentesPlataformaTiles;
	//TMap<TArray<TArray<int>>, AComponentePlataforma*> mComponentesPlataforma2D;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void setPosicionInicial(FVector _posicionInicial) { posicionInicial = _posicionInicial; };
	void setNumeroPisos(int _numeroPisos) { numeroPisos = _numeroPisos; };
	void setNumeroComponentesPorPiso(int _numeroComponentesPorPiso) { numeroComponentesPorPiso = _numeroComponentesPorPiso; };
	void setAlturaEntrePisos(float _alturaEntrePisos) { alturaEntrePisos = _alturaEntrePisos; };
	void setAlturaComponente(float _alturaComponente) { alturaComponente = _alturaComponente; };
	void setAnchoComponente(float _anchoComponente) { anchoComponente = _anchoComponente; };
	void setProfundidadComponente(float _profundidadComponente) { profundidadComponente = _profundidadComponente; };
	void setSeparacionComponentes(float _separacionComponentes) { separacionComponentes = _separacionComponentes; };
	void generarPlataforma();
	void destruirPlataforma();
	void destruirComponentePlataforma(FVector posicion);
	
	AComponentePlataforma* getComponentePlataforma(FVector posicion);
	AComponentePlataforma* getComponentePlataformaTiles(int piso, int componente);

	FVector getPosicionInicial() { return posicionInicial; };
	int getNumeroPisos() { return numeroPisos; };
	int getNumeroComponentesPorPiso() { return numeroComponentesPorPiso; };
	float getAlturaEntrePisos() { return alturaEntrePisos; };
	float getAlturaComponente() { return alturaComponente; };
	float getAnchoComponente() { return anchoComponente; };
	float getProfundidadComponente() { return profundidadComponente; };
	float getSeparacionComponentes() { return separacionComponentes; };
	TMap<FVector, AComponentePlataforma*> getComponentesPlataforma() { return mComponentesPlataforma; };

	void EliminarComponenteAleatorio();
};
