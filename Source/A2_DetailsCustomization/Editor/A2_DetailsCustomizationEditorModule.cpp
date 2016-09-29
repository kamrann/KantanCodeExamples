// Copyright 2016 Cameron Angus

#include "A2_DetailsCustomizationEditorPCH.h"
#include "PropertyEditorModule.h"
#include "A2_MyClassCustomization.h"


/*
Module implementation
*/
class FA2EditorModule: public FDefaultGameModuleImpl
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

void FA2EditorModule::StartupModule()
{
	// Register detail customizations
	{
		auto& PropertyModule = FModuleManager::LoadModuleChecked< FPropertyEditorModule >("PropertyEditor");

		PropertyModule.RegisterCustomClassLayout(
			"A2_MyClass",
			FOnGetDetailCustomizationInstance::CreateStatic(&A2_DetailsCustomization::FMyClassCustomization::MakeInstance)
		);

		PropertyModule.NotifyCustomizationModuleChanged();
	}
}

void FA2EditorModule::ShutdownModule()
{
	if(FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
	{
		auto& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

		PropertyModule.UnregisterCustomClassLayout("A2_MyClass");
	}
}

IMPLEMENT_MODULE(FA2EditorModule, A2_DetailsCustomizationEditor);

