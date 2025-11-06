// Fill out your copyright notice in the Description page of Project Settings.


#include "Moneda.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AMoneda::AMoneda()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MallaComponenteMoneda = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MallaMoneda"));
	RootComponent = MallaComponenteMoneda;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MallaMoneda(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_NarrowCapsule.Shape_NarrowCapsule'"));

	if (MallaMoneda.Succeeded())
	{
		MallaComponenteMoneda->SetStaticMesh(MallaMoneda.Object);
		MallaComponenteMoneda->SetWorldScale3D(FVector(5.f, 5.f, 0.3f));
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialMoneda(TEXT("Material'/Game/StarterContent/Materials/M_Metal_Gold.M_Metal_Gold'"));

	if(MaterialMoneda.Succeeded())
	{
		MallaComponenteMoneda->SetMaterial(0, MaterialMoneda.Object);
	}
}

// Called when the game starts or when spawned
void AMoneda::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMoneda::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

