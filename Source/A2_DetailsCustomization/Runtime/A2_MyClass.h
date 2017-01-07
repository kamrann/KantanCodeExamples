// Copyright 2016 Cameron Angus

#pragma once

#include "Object.h"
#include "A2_MyClass.generated.h"


/**
* Example class that will be customized in the editor module.
*/
UCLASS(Blueprintable)
class A2_DETAILSCUSTOMIZATION_API UA2_MyClass: public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Cat A")
	FString BaseString;

	UPROPERTY(EditAnywhere, Category = "Cat A")
	int32 Count;

	UPROPERTY(VisibleAnywhere, Category = "Cat B")
	TArray< FString > GeneratedList;
};


