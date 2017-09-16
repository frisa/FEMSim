#pragma once
#include <QTextEdit>
#include <QDateTime>

#include <unordered_map>

class UtilLoggerSingleton
{
private:
	static UtilLoggerSingleton* m_instance;
	UtilLoggerSingleton();

private:
	std::vector<QTextEdit*> m_outputs;

public:
	~UtilLoggerSingleton();

	static UtilLoggerSingleton* instance();

	void addOutput(int & id, QTextEdit * output);
	void log(int id, QString * text);
	void logEx(int id, char* format, ...);
	void vlogEx(int id, char* format, va_list arg);
	char *convert(unsigned int num, int base);
	void removeOutput(int id);
};

