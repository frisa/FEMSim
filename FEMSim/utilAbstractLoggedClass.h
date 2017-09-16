#pragma once
#include "utilLoggerSingleton.h"

class UtilAbstractLoggedClass
{
private:
	UtilLoggerSingleton* lg;

public:
	UtilAbstractLoggedClass();
	~UtilAbstractLoggedClass();
	void log0(char * format, ...) const;
	void log1(char * format, ...);
};

