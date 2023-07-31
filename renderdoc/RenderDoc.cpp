#include "RenderDoc.hpp"

#if defined(_WIN32)
#include <Windows.h> // libloaderapi.h
#endif

namespace
{
#if defined(_WIN32)
	namespace win
	{
		auto get_module()
		{
			return GetModuleHandleA("renderdoc.dll");
		}

		bool is_RenderDoc_attached()
		{
			return get_module() != nullptr;
		}

		RENDERDOC_API_VERSION* load_renderdoc_api()
		{
			auto module_handle = get_module();
			if (module_handle == nullptr)
				return nullptr;

			pRENDERDOC_GetAPI get_api = reinterpret_cast<pRENDERDOC_GetAPI>(GetProcAddress(module_handle, "RENDERDOC_GetAPI"));

			RENDERDOC_API_VERSION* renderdoc_api = nullptr;
			auto result = get_api(eRENDERDOC_API_Version_1_6_0, reinterpret_cast<void**>(&renderdoc_api));

			if (result != 1 || renderdoc_api == nullptr)
			{
				throw RenderDocAPI::RenderDocApiError{};
			}

			return renderdoc_api;
		}
	}
#endif
}

RENDERDOC_API_VERSION* RenderDocAPI::get_api()
{
	if (external_api == nullptr)
	{
		auto result = RenderDocAPI::load();

		if (external_api == nullptr || !result)
		{
			throw RenderDocApiError{};
		}
	}
	return external_api;
}

bool RenderDocAPI::load()
{
#if defined(_WIN32)
	try
	{
		external_api = ::win::load_renderdoc_api();
	}
	catch (RenderDocApiError)
	{
		return false;
	}
	return true;
#else
	return false;
#endif
}

bool RenderDocAPI::is_RenderDoc_attached()
{
#if defined(_WIN32)
	return ::win::is_RenderDoc_attached();
#else
	return false;
#endif
}
