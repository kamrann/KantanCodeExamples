// Copyright 2016 Cameron Angus

#include "A1_GatherSubclasses.h"
#include "KantanCodeExamplesCommon.h"

#include "AssetRegistryModule.h"
#include "ARFilter.h"

#if WITH_EDITOR
#include "KismetEditorUtilities.h"
#endif


namespace A1_GatherSubclasses
{
	namespace Detail
	{
		void GetAllNativeSubclasses(TArray< TAssetSubclassOf< UObject > >& Subclasses, TSubclassOf< UObject > Base, bool bAllowAbstract)
		{
			check(Base);

			if(!Base->IsNative())
			{
				return;
			}

			for(TObjectIterator< UClass > ClassIt; ClassIt; ++ClassIt)
			{
				UClass* Class = *ClassIt;

				// Only interested in native C++ classes
				if(!Class->IsNative())
				{
					continue;
				}

				// Ignore deprecated
				if(Class->HasAnyClassFlags(CLASS_Deprecated | CLASS_NewerVersionExists))
				{
					continue;
				}

#if WITH_EDITOR
				// Ignore skeleton classes (semi-compiled versions that only exist in-editor)
				if(FKismetEditorUtilities::IsClassABlueprintSkeleton(Class))
				{
					continue;
				}
#endif

				// Optionally ignore abstract classes
				if(!bAllowAbstract && Class->HasAnyClassFlags(CLASS_Abstract))
				{
					continue;
				}

				// Check this class is a subclass of Base
				if(!Class->IsChildOf(Base))
				{
					continue;
				}

				Subclasses.Add(Class);
			}
		}

		void GetAllBlueprintSubclasses(TArray< TAssetSubclassOf< UObject > >& Subclasses, TSubclassOf< UObject > Base, bool bAllowAbstract, FString const& Path)
		{
			/*
			For blueprint classes, things are complicated by the fact that the UClass may not have been loaded into memory yet.
			The approach taken here is a bit more complicated than it has to be, but allows us to gather the list of subclasses
			without force loading anything.
			*/

			static const FName GeneratedClassTag = TEXT("GeneratedClass");
			static const FName ClassFlagsTag = TEXT("ClassFlags");

			check(Base);

			// Load the asset registry module
			FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked< FAssetRegistryModule >(FName("AssetRegistry"));
			IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

			FName BaseClassName = Base->GetFName();

			// Use the asset registry to get the set of all class names deriving from Base
			TSet< FName > DerivedNames;
			{
				TArray< FName > BaseNames;
				BaseNames.Add(BaseClassName);

				TSet< FName > Excluded;
				AssetRegistry.GetDerivedClassNames(BaseNames, Excluded, DerivedNames);
			}

			// Set up a filter and then pull asset data for all blueprints in the specified path from the asset registry.
			// Note that this works in packaged builds too. Even though the blueprint itself cannot be loaded, its asset data
			// still exists and is tied to the UBlueprint type.
			FARFilter Filter;
			Filter.ClassNames.Add(UBlueprint::StaticClass()->GetFName());
			Filter.bRecursiveClasses = true;
			if(!Path.IsEmpty())
			{
				Filter.PackagePaths.Add(*Path);
			}
			Filter.bRecursivePaths = true;

			TArray< FAssetData > AssetList;
			AssetRegistry.GetAssets(Filter, AssetList);

			// Iterate over retrieved blueprint assets
			for(auto const& Asset : AssetList)
			{
				// Get the the class this blueprint generates (this is stored as a full path)
				if(auto GeneratedClassPathPtr = Asset.TagsAndValues.Find(GeneratedClassTag))
				{
					// Optionally ignore abstract classes
					// As of 4.12 I do not believe blueprints can be marked as abstract, but this may change so included for completeness.
					if(!bAllowAbstract)
					{
						if(auto ClassFlagsPtr = Asset.TagsAndValues.Find(ClassFlagsTag))
						{
							auto ClassFlags = FCString::Atoi(**ClassFlagsPtr);
							if((ClassFlags & CLASS_Abstract) != 0)
							{
								continue;
							}
						}
					}

					// Convert path to just the name part
					const FString ClassObjectPath = FPackageName::ExportTextPathToObjectPath(*GeneratedClassPathPtr);
					const FString ClassName = FPackageName::ObjectPathToObjectName(ClassObjectPath);

					// Check if this class is in the derived set
					if(!DerivedNames.Contains(*ClassName))
					{
						continue;
					}

					// Store using the path to the generated class
					Subclasses.Add(TAssetSubclassOf< UObject >(FStringAssetReference(ClassObjectPath)));
				}
			}
		}
	}
}


void UA1_GatherSubclasses::PrintSubclasses()
{
	if(BaseClass)
	{
		UE_LOG(LogKantanCode, Log, TEXT("[%s] Subclasses gathered with base '%s':"), *GetName(), *BaseClass->GetName());
		for(auto& AssetClass : DerivedSet)
		{
			auto LoadedClass = AssetClass.LoadSynchronous();
			UE_LOG(LogKantanCode, Log, TEXT("%s %s"), AssetClass.IsNull() ? TEXT("[NONE]") : *AssetClass.GetUniqueID().ToString(), !AssetClass.IsNull() && !LoadedClass ? TEXT("_LOAD FAILED_") : TEXT(""));
		}
	}
}

void UA1_GatherSubclasses::Gather()
{
	DerivedSet.Empty();

	if(BaseClass)
	{
		A1_GatherSubclasses::GetAllNativeSubclasses(DerivedSet, BaseClass, bAllowAbstract);
		A1_GatherSubclasses::GetAllBlueprintSubclasses(DerivedSet, BaseClass, bAllowAbstract, FString());
	}
}

void UA1_GatherSubclasses::PostLoad()
{
	Super::PostLoad();

	if(!IsTemplate())
	{
//		Gather();
	}
}


#if WITH_EDITOR

void UA1_GatherSubclasses::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	static const FName NAME_Base = GET_MEMBER_NAME_CHECKED(UA1_GatherSubclasses, BaseClass);
	static const FName NAME_AllowAbstract = GET_MEMBER_NAME_CHECKED(UA1_GatherSubclasses, bAllowAbstract);

	if(PropertyChangedEvent.Property != nullptr)
	{
		const FName PropName = PropertyChangedEvent.MemberProperty->GetFName();
		if(PropName == NAME_Base || PropName == NAME_AllowAbstract)
		{
//			Gather();
		}
	}

	Super::PostEditChangeProperty(PropertyChangedEvent);
}

#endif

