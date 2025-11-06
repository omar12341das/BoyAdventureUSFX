// Fill out your copyright notice in the Description page of Project Settings.


#include "ComponentePlataforma.h"

// Sets default values
AComponentePlataforma::AComponentePlataforma()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MallaComponentePlataforma = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MallaComponentePlataforma"));
	RootComponent = MallaComponentePlataforma;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MallaPlataforma(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));

	if (MallaPlataforma.Succeeded())
	{
		MallaComponentePlataforma->SetStaticMesh(MallaPlataforma.Object);
		MallaComponentePlataforma->SetWorldScale3D(FVector(1.5f, 2.0f, 0.2f));
	}



}

float DesplazamientoPZ = 100.0f;
float DesplazamientoNZ = 100.0f;;
float DesplazamientoPX = 1000.0f;
float DesplazamientoNX = 1000.0f;
float DesplazamientoPY = 100.0f;
float DesplazamientoNY = 100.0f;
bool bMovimiento= false ;
float IncrementoX;
// Called when the game starts or when spawned
void AComponentePlataforma::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AComponentePlataforma::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*/if (bMoviendo)
	{
		FVector posicionActual = GetActorLocation();
		FVector direccion = (DestinoMovimiento - posicionActual).GetSafeNormal();
	    float distancia = FVector::Dist(posicionActual, DestinoMovimiento);
		float paso = VelocidadMovimiento * DeltaTime;
		if (distancia > paso)
		{
			SetActorLocation(posicionActual + direccion * paso);
		}
		else
		{
			SetActorLocation(DestinoMovimiento);
			bMoviendo = false;
		}
	}*/
	Moverse();
}

void AComponentePlataforma::Moverse() {
	if (bMovimiento) {
		FVector posicionActual = GetActorLocation();
		if (PosicionInicial.X < (posicionActual.X + DesplazamientoPX))
		{
			IncrementoX = -10.0f;
		}
		if(posicionActual.X <= (posicionActual.X - DesplazamientoNX)){
			IncrementoX = 1.0f;
		}
		posicionActual.X += IncrementoX;
		SetActorLocation(posicionActual);
	}
}