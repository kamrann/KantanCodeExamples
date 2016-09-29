// Copyright 2016 Cameron Angus

#include "A2_DetailsCustomizationEditorPCH.h"
#include "A2_MyClassCustomization.h"
#include "A2_MyClass.h"
#include "PropertyEditing.h"

#define LOCTEXT_NAMESPACE "A2"


namespace A2_DetailsCustomization
{
	TSharedRef< IDetailCustomization > FMyClassCustomization::MakeInstance()
	{
		return MakeShareable(new FMyClassCustomization);
	}

	void FMyClassCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
	{
		TArray< TWeakObjectPtr< UObject > > Objects;
		DetailBuilder.GetObjectsBeingCustomized(Objects);

		if(Objects.Num() != 1)
		{
			return;
		}

		TWeakObjectPtr< UA2_MyClass > MyObject = Cast< UA2_MyClass >(Objects[0].Get());

		auto& Cat = DetailBuilder.EditCategory(TEXT("Custom"));

		/*
		Showing a warning message about invalid property values.
		(Note that customizations can also be used to enforce validation on user-entered property values).
		*/
		auto OnGetWarningVisibility = [MyObject]
		{
			return MyObject.IsValid() && MyObject->BaseString.IsEmpty() ? EVisibility::Visible : EVisibility::Collapsed;
		};
		auto WarningVisibilityAttr = TAttribute< EVisibility >::Create(TAttribute< EVisibility >::FGetter::CreateLambda(OnGetWarningVisibility));

		Cat.AddCustomRow(LOCTEXT("MyWarningRowFilterString", "Search Filter Keywords"))
			.Visibility(WarningVisibilityAttr)
			.WholeRowContent()
			[
				SNew(STextBlock)
				.Text(LOCTEXT("MyWarningTest", "BaseString should not be empty!"))
			];

		/*
		Displaying a button that triggers editor-time processing.
		*/
		auto OnRegenerate = [MyObject]
		{
			if(MyObject.IsValid())
			{
				MyObject->GeneratedList.Empty();
				for(int32 i = 0; i < MyObject->Count; ++i)
				{
					MyObject->GeneratedList.Add(MyObject->BaseString + TEXT("_") + (MyObject->Count + 1));
				}
			}

			return FReply::Handled();
		};

		Cat.AddCustomRow(LOCTEXT("MyButtonRowFilterString", "Search Filter Keywords"))
			.WholeRowContent()
			[
				SNew(SButton)
				.Text(LOCTEXT("RegenerateBtnText", "Regenerate List"))
				.OnClicked_Lambda(OnRegenerate)
			];
	}
}


#undef LOCTEXT_NAMESPACE

