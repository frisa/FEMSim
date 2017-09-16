#include "utilLoggerSingleton.h"

UtilLoggerSingleton* UtilLoggerSingleton::m_instance = 0;

UtilLoggerSingleton::UtilLoggerSingleton()
{
    /* Do nothing here men !! */
}

UtilLoggerSingleton::~UtilLoggerSingleton()
{
}

UtilLoggerSingleton * UtilLoggerSingleton::instance()
{
    if (!m_instance)
    {
        m_instance = new UtilLoggerSingleton();
    }
    return m_instance;
}

void UtilLoggerSingleton::addOutput(int& id, QTextEdit * output)
{
    m_outputs.push_back(output);
    id = m_outputs.size() - 1;
}

void UtilLoggerSingleton::log(int id, QString * text)
{
    m_outputs.at(id)->setPlainText(*text);
}

void UtilLoggerSingleton::logEx(int id, char * format, ...)
{

}

void UtilLoggerSingleton::vlogEx(int id, char * format, va_list arg)
{
    char out[500];
    int outIdx = 0;
    unsigned int u32FetchNumber = 0;
    char* cFetchNumber;
    char* ch;

	ch = format;
    while ('\0' != *ch)
    {
		if ('%' != *ch)
		{
			out[outIdx++] = *ch++;
			continue;
		}
        switch (*++ch)
        {
            case 'd':
            {
                u32FetchNumber = va_arg(arg, int);
                if (0 > u32FetchNumber)
                {
                    u32FetchNumber = -u32FetchNumber;
                    out[outIdx++] = '-';
                }
                cFetchNumber = convert(u32FetchNumber, 10);
                strcpy(&out[outIdx], cFetchNumber);
                outIdx = outIdx + strlen(cFetchNumber);
                break;
            }
            case 'x':
            {
                u32FetchNumber = va_arg(arg, unsigned int);
                cFetchNumber = convert(u32FetchNumber, 16);
                strcpy(&out[outIdx], cFetchNumber);
                outIdx = outIdx + strlen(cFetchNumber);
                break;
            }
            case 's':
            {
                cFetchNumber = va_arg(arg, char *);
                if (cFetchNumber)
                {
                    strcpy(&out[outIdx], cFetchNumber);
                    outIdx = outIdx + strlen(cFetchNumber);
                }
                else
                {
                    strcpy(&out[outIdx], "NULL");
                    outIdx = outIdx + strlen("NULL");
                }
                break;
            }
            default:
            {
                break;
            }
        }
		ch++;
    }
	out[outIdx++] = '\n';
	out[outIdx++] = '\0';
	m_outputs.at(id)->moveCursor(QTextCursor::End);

	QString sTimeOutput = "[" + QDateTime::currentDateTime().time().toString() + "] " + QString(out);

	m_outputs.at(id)->insertPlainText(sTimeOutput);
	m_outputs.at(id)->moveCursor(QTextCursor::End);
}

char * UtilLoggerSingleton::convert(unsigned int num, int base)
{
    static char Representation[] = "0123456789ABCDEF";
    static char buffer[50];
    char *ptr;

    ptr = &buffer[49];
    *ptr = '\0';

    do
    {
        *--ptr = Representation[num%base];
        num /= base;
    } while (num != 0);

    return(ptr);
}

void UtilLoggerSingleton::removeOutput(int id)
{
}

