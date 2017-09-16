#include "utilAbstractLoggedClass.h"



UtilAbstractLoggedClass::UtilAbstractLoggedClass()
{
	lg = UtilLoggerSingleton::instance();
}

UtilAbstractLoggedClass::~UtilAbstractLoggedClass()
{
}

void UtilAbstractLoggedClass::log0(char* format, ...) const
{
	va_list args;
	va_start(args, format);
	lg->vlogEx(0, format, args);
	va_end(args);
}

void UtilAbstractLoggedClass::log1(char* format, ...)
{
	va_list args;
	va_start(args, format);
	lg->vlogEx(1, format, args);
	va_end(args);
}
