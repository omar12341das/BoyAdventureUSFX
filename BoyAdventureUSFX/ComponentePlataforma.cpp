// Fill out your copyright notice in the Description page of Project Settings.


#include "ComponentePlataforma.h"

// Sets default values
AComponentePlataforma::AComponentePlataforma()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MallaComponentePlataforma = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MallaComponentePlataforma"));
	RootComponent = MallaComponentePlataforma;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MallaPlataforma(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
	
	if (MallaPlataforma.Succeeded())
	{
		MallaComponentePlataforma->SetStaticMesh(MallaPlataforma.Object);
		MallaComponentePlataforma->SetWorldScale3D(FVector(2.0f, 2.0f, 0.2f));
	}
	


}

// Called when the game starts or when spawned
void AComponentePlataforma::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AComponentePlataforma::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

