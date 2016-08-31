// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreUObject.h"
#include "_1_GatherSubclasses.generated.h"


namespace _1_GatherSubclasses
{
	namespace Detail
	{
		void GetAllNativeSubclasses(TArray< TAssetSubclassOf< UObject > >& OutSubclasses, TSubclassOf< UObject > Base, bool bAllowAbstract);
		void GetAllBlueprintSubclasses(TArray< TAssetSubclassOf< UObject > >& OutSubclasses, TSubclassOf< UObject > Base, bool bAllowAbstract, FString const& Path);
	}

	template < typename TBase >
	void GetAllNativeSubclasses(TArray< TAssetSubclassOf< TBase > >& Subclasses, TSubclassOf< TBase > Base, bool bAllowAbstract)
	{
		TArray< TAssetSubclassOf< UObject > > Classes;
		Detail::GetAllNativeSubclasses(Classes, Base, bAllowAbstract);
		for(auto const& Cls : Classes)
		{
			Subclasses.Add(Cls);
		}
	}

	template < typename TBase >
	void GetAllBlueprintSubclasses(TArray< TAssetSubclassOf< TBase > >& Subclasses, TSubclassOf< TBase > Base, bool bAllowAbstract, FString const& Path)
	{
		TArray< TAssetSubclassOf< UObject > > Classes;
		Detail::GetAllBlueprintSubclasses(Classes, Base, bAllowAbstract, Path);
		for(auto const& Cls : Classes)
		{
			Subclasses.Add(Cls);
		}
	}
}


/**
* Example class using properties to demonstrate gathering of all subclasses (native and blueprint) of a given class.
*/
UCLASS(Blueprintable)
class UArticle1_GatherSubclasses: public UObject
{
	GENERATED_BODY()

public:
	/** The base class, for which we want to find all derived classes/blueprints */
	UPROPERTY(EditAnywhere, Category = "Example", Meta = (AllowAbstract = "true"))
	TSubclassOf< UObject > BaseClass;

	/** Whether to include abstract classes in the results */
	UPROPERTY(EditAnywhere, Category = "Example")
	bool bAllowAbstract;

	/** Generated results */
	UPROPERTY(Transient, VisibleAnywhere, Category = "Example")
	TArray< TAssetSubclassOf< UObject > > DerivedSet;

protected:
	void Gather();

public:
	virtual void PostLoad() override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
};


