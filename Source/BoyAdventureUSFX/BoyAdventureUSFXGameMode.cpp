// Copyright Epic Games, Inc. All Rights Reserved.

#include "BoyAdventureUSFXGameMode.h"
#include "BoyAdventureUSFXCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "ObstaculoPared.h"
#include "ParedMetal.h"
#include "TrampaSierra.h"
#include "Obstaculo.h"
#include "Plataforma.h"
#include "Moneda.h"

ABoyAdventureUSFXGameMode::ABoyAdventureUSFXGameMode()
{
    // set default pawn class to our Blueprinted character
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
    if (PlayerPawnBPClass.Class != NULL)
    {
        DefaultPawnClass = PlayerPawnBPClass.Class;
		//PlayerPawnBPClass->SetActorLocation(FVector(400.f, 300.f, 0.f));
        //Definir la posicion  inicial del jugador

    }
}

void ABoyAdventureUSFXGameMode::BeginPlay()
{

    // Verifica que el mundo esté disponible
    UWorld* Mundo = GetWorld();
    if (Mundo)
    {
        //CrearObstaculos();


        Plataforma01 = Mundo->SpawnActor<APlataforma>(APlataforma::StaticClass());
        if (Plataforma01)
        {
            Plataforma01->setAltoEntrePisos(200.f);
            Plataforma01->setAltoComponente(20.f);
            Plataforma01->setAnchoComponente(200.f);
            Plataforma01->setProfundidadComponente(100.f);
            Plataforma01->setSeparacionComponentes(50.f);
            Plataforma01->setPosicionInicial(FVector(-700.f, -300.f, 250.f));
            Plataforma01->generarPlataforma();
        }


        //FVector UTS01(100.0f, -500.0f, 500.0f); // Ajusta según tu escena
        //FRotator RTS01(0.0f, 0.0f, 0.0f);

        //ts01 = Mundo->SpawnActor<ATrampaSierra>(ATrampaSierra::StaticClass(), UTS01, RTS01);

        //if (ts01)
        //{
        //    UE_LOG(LogTemp, Warning, TEXT("trampa sierra 01 creada exitosamente"));
        //}

        //FVector UTS02(400.0f, -500.0f, 400.0f); // Ajusta según tu escena
        //FRotator RTS02(0.0f, 0.0f, 0.0f);

        //ts02 = Mundo->SpawnActor<ATrampaSierra>(ATrampaSierra::StaticClass(), UTS02, RTS02);

        //if (ts02)
        //{
        //    UE_LOG(LogTemp, Warning, TEXT("trampa sierra 02 creada exitosamente"));
        //}


        //// Define la ubicación y rotación del obstáculo
        FVector Ubicacion(0.0f, 0.0f, 400.0f); // Ajusta según tu escena
        FRotator Rotacion(0.0f, 0.0f, 0.0f);

        //// Spawnea el actor
        FActorSpawnParameters ParametrosSpawn;
        ParametrosSpawn.Owner = this;
        ParametrosSpawn.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

        Obstaculo = Mundo->SpawnActor<AObstaculoPared>(AObstaculoPared::StaticClass(), Ubicacion, Rotacion, ParametrosSpawn);

        if (Obstaculo)
        {

            UE_LOG(LogTemp, Warning, TEXT("Obstáculo creado exitosamente"));
        }
        //pawn pricipal
        FVector PosicionInicial(400.f,300.f, 0.f);
		FRotator Rotacion03(0.f);
		PawnPrincipal = Mundo->SpawnActor<ABoyAdventureUSFXCharacter>(ABoyAdventureUSFXCharacter::StaticClass(), PosicionInicial, Rotacion03, ParametrosSpawn);

        //// Define la ubicación y rotación del obstáculo
        FVector Ubicacion01(200.0f, -300.0f, 400.0f); // Ajusta según tu escena
        FRotator Rotacion02(0.0f, 0.0f, 0.0f);

        ParedMetal01 = Mundo->SpawnActor<AParedMetal>(AParedMetal::StaticClass(), Ubicacion, Rotacion);

        //spwanear la moneda
		FVector UbicacionMoneda(300.0f, 300.0f, 500.0f); // Ajusta según tu escena
		FRotator RotacionMoneda(0.0f, 0.0f, 90.0f);
        
		moneda01 = Mundo->SpawnActor<AMoneda>(AMoneda::StaticClass(), UbicacionMoneda, RotacionMoneda, ParametrosSpawn);

    }

    /*GetWorld()->GetTimerManager().SetTimer(
        EliminarComponentePlataformaTimer,
        this,
        &ABoyAdventureUSFXGameMode::EliminarComponentePlataforma,
        Intervalo,
        true
    );*/

    GetWorld()->GetTimerManager().SetTimer(
        MovimientoComponentesPlataformaTimer,
        this,
        &ABoyAdventureUSFXGameMode::MoverComponentePlataforma,
        Intervalo,
        true
    );

    GetWorld()->GetTimerManager().SetTimer(
        rotarMonedaTimer, this, &ABoyAdventureUSFXGameMode::rotarMoneda, 0.1,true
    );

    /*GetWorld()->GetTimerManager().SetTimer(
        MoverComponentePlataformaTimer, // El handle del timer
        this,                       // El objeto que tiene la función
        &ABoyAdventureUSFXGameMode::MoverComponentePlataformaTimer, // La función a llamar
        2.f,                     // Intervalo en segundos
        true                        // Repetir (true = sí, false = solo una vez)
    );*/

    /*GetWorld()->GetTimerManager().SetTimer(
        MovimientoTimer,
        this,
        &ABoyAdventureUSFXGameMode::MoverActorAleatoriamente,
        Intervalo,
        true
    );*/
  
    
    for (int32 i = 0; i < aObstaculos.Num(); ++i)
    {
        if (aObstaculos[i])
        {
            aObstaculos[i]->Activarse();
        }
    }
    
    rotarMoneda();
    /*
    for (int32 i = 25; i < aObstaculos.Num(); ++i)
    {
        if (aObstaculos[i])
        {
            aObstaculos[i]->Desactivarse();
        }
    }

    aObstaculos[17]->Desactivarse();
    */
}


/*void ABoyAdventureUSFXGameMode::EliminarComponentePlataforma()
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Eliminando componente plataforma"));

    if (Plataforma01)
    {
        Plataforma01->EliminarComponenteAleatorio();
    }
}*/
void ABoyAdventureUSFXGameMode::MoverComponentePlataforma() {
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Componente en movimiento"));
    if (Plataforma01)
    {
        Plataforma01->MoverComponentePlataforma();
    }
}

void ABoyAdventureUSFXGameMode::CrearObstaculos()
{
    FVector PosicionInicial(-200.f, 200.f, 300.f); // Altura inicial
    float Espaciado = 150.f;

    for (int32 i = 0; i < 15; ++i)
    {
        FVector SpawnLocation = PosicionInicial + FVector(i * Espaciado, 0.f, 0.f);
        FRotator SpawnRotation = FRotator::ZeroRotator;

        AObstaculo* NuevoObstaculo = GetWorld()->SpawnActor<AObstaculo>(AObstaculo::StaticClass(), SpawnLocation, SpawnRotation);
        if (NuevoObstaculo)
        {
            aObstaculos.Add(NuevoObstaculo);
        }
    }

    PosicionInicial = FVector(-200.f, -600.f, 300.f); // Altura inicial
    for (int32 i = 0; i < 25; ++i)
    {
        FVector SpawnLocation = PosicionInicial + FVector(0.f, i * Espaciado, 0.f);
        FRotator SpawnRotation = FRotator::ZeroRotator;

        AObstaculo* NuevaParedMetal = GetWorld()->SpawnActor<AParedMetal>(AParedMetal::StaticClass(), SpawnLocation, SpawnRotation);
        if (NuevaParedMetal)
        {
            aObstaculos.Add(NuevaParedMetal);
        }
    }
}


void ABoyAdventureUSFXGameMode::MoverActorAleatoriamente()
{
    FVector PosicionActual = Obstaculo->GetActorLocation();

    float NuevoX = FMath::RandRange(-RangoMovimiento.X, RangoMovimiento.X);
    float NuevoY = FMath::RandRange(-RangoMovimiento.Y, RangoMovimiento.Y);

    FVector NuevaPosicion = FVector(NuevoX, NuevoY, PosicionActual.Z);

    Obstaculo->SetActorLocation(NuevaPosicion);

    // Obtén el actor principal del mundo  
    /*AActor* OwnerActor = Cast<AActor>(GetOwner());
    if (OwnerActor)
    {
        FVector PosicionActual = OwnerActor->GetActorLocation();

        float NuevoX = FMath::RandRange(-RangoMovimiento.X, RangoMovimiento.X);
        float NuevoY = FMath::RandRange(-RangoMovimiento.Y, RangoMovimiento.Y);

        FVector NuevaPosicion = FVector(NuevoX, NuevoY, PosicionActual.Z);

        OwnerActor->SetActorLocation(NuevaPosicion);
    }  */
}


void ABoyAdventureUSFXGameMode::rotarMoneda()
{

    float velocidadRotacion = 10.0f;
    float anguloMaximoRotacion = 90.0f;
    float anguloMinimoRotacion = 0.0f;

    if (moneda01)
    {
        FRotator RotacionActual = moneda01->GetActorRotation();
        RotacionActual.Yaw += velocidadRotacion * direccionRotacion;
        moneda01->SetActorRotation(RotacionActual);

        // Cambia la dirección si se alcanza el máximo o el mínimo
        if (RotacionActual.Yaw >= anguloMaximoRotacion)
        {
            direccionRotacion = -1.0f;
        }
        else if (RotacionActual.Yaw <= anguloMinimoRotacion)
        {
            direccionRotacion = 1.0f;
        }
    }
}
/* {
    Super::Tick(DeltaSeconds);
    // Aquí puedes agregar cualquier lógica que necesites ejecutar cada frame
}*/

/*void ABoyAdventureUSFXGameMode::UbicarAleatoriamentePawn()
{
   
   
}*/
