// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EstadoEnemigo.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEstadoEnemigo : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BOYADVENTUREUSFX_API IEstadoEnemigo
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void atacar = 0;
	virtual void moverse 0;
};
