// Fill out your copyright notice in the Description page of Project Settings.


#include "Plataforma.h"
#include "ComponentePlataforma.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
APlataforma::APlataforma()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	posicionInicial = FVector(100.f, 100.f, 100.f);
	//numeroPisos = 1;
	//numeroComponentesPorPiso = 10;
	altoEntrePisos = 100.f;
	altoComponente = 20.f;
	anchoComponente = 100.f;
	profundidadComponente = 100.f;
	separacionComponentes = 50.f;


	//mComponentesPorPiso.Add(1, 10);
	//mComponentesPorPiso.Add(2, 20);
	//mComponentesPorPiso.Add(3, 5); 
	//mComponentesPorPiso[0] = 10;
	//mComponentesPorPiso[1] = 20;
	//mComponentesPorPiso[2] = 5;

	mComponentesPorPiso = { { 1, 10 }, { 2, 12 }, { 3, 10 }, {4, 10}, {5, 10} };
}



// Called when the game starts or when spawned
void APlataforma::BeginPlay()
{
	Super::BeginPlay();

	//generarPlataforma();
}

// Called every frame
void APlataforma::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlataforma::generarPlataforma()
{
	int numeroPisos = mComponentesPorPiso.Num();
	int numeroComponentesPorPiso = 0;

	for (int i = 0; i < numeroPisos; i++)
	{
		numeroComponentesPorPiso = mComponentesPorPiso[i + 1]; // i+1 porque los pisos empiezan en 1 y no en 0
		for (int j = 0; j < numeroComponentesPorPiso; j++)
		{
			FVector posicionComponente = getPosicionInicial() + FVector(j * (anchoComponente + separacionComponentes), 0.f, i * (altoComponente + altoEntrePisos));

			int llave = (i + 1) * 100 + j; // Genera una llave unica para cada componente basado en su piso y posicion
			AComponentePlataforma* nuevoComponente = GetWorld()->SpawnActor<AComponentePlataforma>(AComponentePlataforma::StaticClass(), posicionComponente, FRotator::ZeroRotator);
			if (nuevoComponente)
			{
				mComponentesPlataformaTiles.Add(llave, nuevoComponente);
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

AComponentePlataforma* APlataforma::getComponentePlataforma(int _piso, int _numeroComponente)
{
	int llave = _piso * 100 + _numeroComponente; // Genera una llave unica para cada componente basado en su piso y posicionint llave = _piso * 100 + _numeroComponente; // Genera una llave unica para cada componente basado en su piso y posicion

	if (mComponentesPlataformaTiles.Contains(llave))
	{
		return mComponentesPlataformaTiles[llave];
	}

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

AComponentePlataforma* APlataforma::getComponentePlataformaTiles(int32 piso, int32 componente)
{
	/*if (mComponentesPlataforma2D.Contains({ {piso}, {componente} })
	{
		return mComponentesPlataforma2D[{piso, componente}];
	}*/

	return nullptr; // Valor por defecto si el índice no es válido
}


void APlataforma::MoverComponentePlataforma()
{
	if (mComponentesPlataformaTiles.Num() == 0) return;

	// Supongamos que ya tienes mComponentesPorPiso poblado
	int32 PisoAleatorio = -1;
	int32 ComponenteAleatorio = -1;

	if (mComponentesPorPiso.Num() > 0)
	{
		// Obtener todas las claves (pisos)
		TArray<int32> Pisos;
		mComponentesPorPiso.GetKeys(Pisos);

		// Seleccionar un piso aleatorio
		int32 IndexPiso = FMath::RandRange(0, Pisos.Num() - 1);
		PisoAleatorio = Pisos[IndexPiso];

		// Obtener el número de componentes en ese piso
		int32 NumComponentes = mComponentesPorPiso[PisoAleatorio];

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Piso aleatorio: %d con %d componentes"), PisoAleatorio, NumComponentes));
		// Seleccionar un componente aleatorio dentro del rango
		if (NumComponentes > 0)
		{
			ComponenteAleatorio = FMath::RandRange(1, NumComponentes); // Asumiendo que los componentes van de 1 a N
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("El piso %d no tiene componentes."), PisoAleatorio);
			return;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("mComponentesPorPiso est?? vac?o."));
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, FString::Printf(TEXT("Componente aleatorio: %d en piso %d"), ComponenteAleatorio, PisoAleatorio));

	int32 KeySeleccionada = PisoAleatorio * 100 + ComponenteAleatorio;

	AComponentePlataforma* componentePlataformaActual = nullptr;
	if (mComponentesPlataformaTiles.Contains(KeySeleccionada))
	{
		componentePlataformaActual = mComponentesPlataformaTiles[KeySeleccionada];
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("No se encontr?? el componente en piso %d, componente %d"), PisoAleatorio, ComponenteAleatorio));
		UE_LOG(LogTemp, Warning, TEXT("No se encontr?? el componente en piso %d, componente %d"), PisoAleatorio, ComponenteAleatorio);
		return;
	}

	// Obtener y destruir el actor
	if (componentePlataformaActual)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Moviendo componente en piso %d, componente %d"), PisoAleatorio, ComponenteAleatorio));

		/*FVector posicionActual = componentePlataformaActual->GetActorLocation();
		float desplazamientoX = FMath::RandRange(-200.f, -50.f);
		FVector nuevaPosicion = posicionActual + FVector(desplazamientoX, 0.f, 0.f);
		componentePlataformaActual->SetActorLocation(nuevaPosicion);*/

		if (componentePlataformaActual)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Animando componente en piso %d,componente %d"), PisoAleatorio, ComponenteAleatorio));
		//FVector posocionActual = posicionActual + FVector(desplazamientoX, 0.f, 0.f);

		//componentePlataformaActual->DestinoMovimiento = nuevaPosicion;
		componentePlataformaActual->bMovimiento = true;
		
		//UE_LOG(LogTemp, Warning, TEXT("Componente eliminado en %s"), *KeySeleccionada.ToString());
	}
}

/*void APlataforma::EliminarComponenteAleatorio()
{
	if (mComponentesPlataformaTiles.Num() == 0) return;

	// Supongamos que ya tienes mComponentesPorPiso poblado
	int32 PisoAleatorio = -1;
	int32 ComponenteAleatorio = -1;

	if (mComponentesPorPiso.Num() > 0)
	{
		// Obtener todas las claves (pisos)
		TArray<int32> Pisos;
		mComponentesPorPiso.GetKeys(Pisos);

		// Seleccionar un piso aleatorio
		int32 IndexPiso = FMath::RandRange(0, Pisos.Num() - 1);
		PisoAleatorio = Pisos[IndexPiso];

		// Obtener el número de componentes en ese piso
		int32 NumComponentes = mComponentesPorPiso[PisoAleatorio];

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Piso aleatorio: %d con %d componentes"), PisoAleatorio, NumComponentes));
		// Seleccionar un componente aleatorio dentro del rango
		if (NumComponentes > 0)
		{
			ComponenteAleatorio = FMath::RandRange(1, NumComponentes); // Asumiendo que los componentes van de 1 a N
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("El piso %d no tiene componentes."), PisoAleatorio);
			return;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("mComponentesPorPiso est?? vac?o."));
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, FString::Printf(TEXT("Componente aleatorio: %d en piso %d"), ComponenteAleatorio, PisoAleatorio));

	int32 KeySeleccionada = PisoAleatorio * 100 + ComponenteAleatorio;

	AComponentePlataforma* componentePlataformaActual = nullptr;
	if (mComponentesPlataformaTiles.Contains(KeySeleccionada))
	{
		componentePlataformaActual = mComponentesPlataformaTiles[KeySeleccionada];
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("No se encontr?? el componente en piso %d, componente %d"), PisoAleatorio, ComponenteAleatorio));
		UE_LOG(LogTemp, Warning, TEXT("No se encontr?? el componente en piso %d, componente %d"), PisoAleatorio, ComponenteAleatorio);
		return;
	}

	// Obtener y destruir el actor
	if (componentePlataformaActual)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Eliminando componente en piso %d, componente %d"), PisoAleatorio, ComponenteAleatorio));
		componentePlataformaActual->Destroy();
		mComponentesPlataformaTiles.Remove(KeySeleccionada);
		//UE_LOG(LogTemp, Warning, TEXT("Componente eliminado en %s"), *KeySeleccionada.ToString());
	}
}*/




