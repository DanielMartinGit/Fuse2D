#pragma once

#include <iostream>
#include <chrono>

namespace Fuse2DUtils
{
	class Logger
	{
		public:
			Logger();
			~Logger();

		public:
			static void LogMessage(const char* message);
	};
}