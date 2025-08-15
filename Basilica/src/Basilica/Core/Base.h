#pragma once

#include "Tanuki/Core/PlatformDetection.h"

#include <memory>

#ifdef TNK_DEBUG
	#if defined(TNK_PLATFORM_WINDOWS)
		#define TNK_DEBUGBREAK() __debugbreak()
	#elif defined(TNK_PLATFORM_LINUX)
		#include <signal.h>
		#define TNK_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
	#define TNK_ENABLE_ASSERTS
#else
	#define TNK_DEBUGBREAK()
#endif

#define TNK_EXPAND_MACRO(x) x
#define TNK_STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << x)

#define TNK_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace Tanuki {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}

#include "Tanuki/Core/Log.h"
#include "Tanuki/Core/Assert.h"