#pragma once

#include <memory>
#include "core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Hazel {
	class HAZEL_API Log{
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	public:
		static void init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	};
}
//Core log macros
#define HZ_CORE_TRACE(...)     ::Hazel::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define HZ_CORE_INFO(...)      ::Hazel::Log::GetCoreLogger()->info(__VA_ARGS__)
#define HZ_CORE_WARN(...)      ::Hazel::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define HZ_CORE_ERROR(...)     ::Hazel::Log::GetCoreLogger()->error(__VA_ARGS__)
#define HZ_CORE_FATALR(...)    ::Hazel::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//Client log macros
#define HZ_CLIENT_TRACE(...)   ::Hazel::Log::GetClientLogger()-_>trace(__VA_ARGS__)
#define HZ_CLIENT_INFO(...)    ::Hazel::Log::GetClientLogger()->info(__VA_ARGS__)
#define HZ_CLIENT_WARN(...)    ::Hazel::Log::GetClientLogger()->warn(__VA_ARGS__)
#define HZ_CLIENT_ERROR(...)   ::Hazel::Log::GetClientLogger()->error(__VA_ARGS__)
#define HZ_CLIENT_FATALR(...)  ::Hazel::Log::GetClientLogger()->fatal(__VA_ARGS__)
