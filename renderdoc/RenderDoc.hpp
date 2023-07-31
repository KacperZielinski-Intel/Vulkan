#pragma once

#ifndef _RENDERDOC_API_
#define _RENDERDOC_API_

#include <stdexcept>

#include "api/app/renderdoc_app.h"

using RENDERDOC_API_VERSION = RENDERDOC_API_1_6_0;

namespace RenderDocAPI
{
	struct RenderDocApiError : public std::exception
	{
		RenderDocApiError() = default;

		virtual char const* what() const
		{
			return "RenderDoc API has not been loaded!";
		}
	};
}

namespace RenderDocAPI
{
	namespace
	{
		static RENDERDOC_API_VERSION* external_api = nullptr;
	}

	RENDERDOC_API_VERSION* get_api();
	bool load();
	bool is_RenderDoc_attached();
};


#endif //_RENDERDOC_API_