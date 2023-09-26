#include "Logging.h"

Fuse2DUtils::Logger::Logger() {}
Fuse2DUtils::Logger::~Logger() {}

void Fuse2DUtils::Logger::LogMessage(const char* message)
{
	std::cout << message << std::endl;
}