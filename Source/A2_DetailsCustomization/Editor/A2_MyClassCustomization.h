// Copyright 2016 Cameron Angus

#pragma once

#include "IDetailCustomization.h"


namespace A2_DetailsCustomization
{
	class FMyClassCustomization: public IDetailCustomization
	{
	public:
		// IDetailCustomization interface
		virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;
		//

		static TSharedRef< IDetailCustomization > MakeInstance();
	};
}

