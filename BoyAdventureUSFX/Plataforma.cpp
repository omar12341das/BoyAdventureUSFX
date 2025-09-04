// Fill out your copyright notice in the Description page of Project Settings.


#include "Plataforma.h"
#include "ComponentePlataforma.h"


// Sets default values
APlataforma::APlataforma()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	posicionInicial = FVector(100.f, 100.f, 100.f);
	numeroPisos = 1;
	numeroComponentesPorPiso = 10;
	alturaEntrePisos = 50.f;
	alturaComponente = 20.f;
	anchoComponente = 100.f;
	profundidadComponente = 100.f;
	separacionComponentes = 10.f;

}



// Called when the game starts or when spawned
void APlataforma::BeginPlay()
{
	Super::BeginPlay();

	generarPlataforma();
}

// Called every frame
void APlataforma::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlataforma::generarPlataforma()
{
	for (int i = 0; i < numeroPisos; i++)
	{
		for (int j = 0; j < numeroComponentesPorPiso; j++)
		{
			//FVector posicionComponente = FVector(j * anchoComponente + separacionComponentes, getPosicionInicial().Y,  i * (anchoComponente + separacionComponentes));
			FVector posicionComponente = getPosicionInicial() + FVector(j * (anchoComponente + separacionComponentes), 0.f, i * (alturaComponente + alturaEntrePisos));
			//TArray<int, int> key = { i, j };
			AComponentePlataforma* nuevoComponente = GetWorld()->SpawnActor<AComponentePlataforma>(AComponentePlataforma::StaticClass(), posicionComponente, FRotator::ZeroRotator);
			if (nuevoComponente)
			{
				mComponentesPlataforma.Add(posicionComponente, nuevoComponente);
				//mComponentesPlataformaTiles.Add(key, nuevoComponente);
			}
		}
	}

}

void APlataforma::destruirPlataforma()
{
}

void APlataforma::destruirComponentePlataforma(FVector posicion)
{
}

AComponentePlataforma* APlataforma::getComponentePlataforma(FVector posicion)
{
	return nullptr;
}

//AComponentePlataforma* APlataforma::getComponentePlataforma2D(int piso, int componente)
//{
//	TArray<TArray<int> key = { piso, componente };
//	if (mComponentesPlataforma2D.Contains(key))
//	{
//		return mComponentesPlataforma2D[key];
//	}
//
//	return nullptr;
//}

AComponentePlataforma* APlataforma::getComponentePlataformaTiles(int piso, int componente)
{
	/*if (mComponentesPlataforma2D.Contains({ {piso}, {componente} })
	{
		return mComponentesPlataforma2D[{piso, componente}];
	}*/

	return nullptr; // Valor por defecto si el índice no es válido
}

void APlataforma::EliminarComponenteAleatorio()
{
	/*
	if (mComponentesPlataforma2D.Num() == 0) return;

	// Obtener todas las llaves
	TArray<TArray<int, int>> Keys;
	mComponentesPlataforma2D.GetKeys(Keys);

	// Seleccionar una aleatoria
	int32 Index = FMath::RandRange(0, Keys.Num() - 1);
	TArray<int, int> KeySeleccionada = Keys[Index];

	// Obtener y destruir el actor
	if (AComponentePlataforma* Componente = mComponentesPlataforma2D[KeySeleccionada])
	{
		Componente->Destroy();
		mComponentesPlataforma2D.Remove(KeySeleccionada);
		//UE_LOG(LogTemp, Warning, TEXT("Componente eliminado en %s"), *KeySeleccionada.ToString());
	}
	*/
}


