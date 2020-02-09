#ifndef _duration_h_
#define _duration_h_

#include <Windows.h>

class stopwatch
{
	double	m_pcFreq;
	__int64 m_counterStart;
	double m_duration;
	char m_str[100];

	void clear()
	{
		m_pcFreq = 0.0;
		m_counterStart = 0;
		m_duration = 0.0;
	}
public:
	stopwatch():m_pcFreq(0.0), m_counterStart(0), m_duration(0.0)
	{
	};
	virtual ~stopwatch(){};

	bool start()
	{ 
		clear();
		LARGE_INTEGER li;
		if(!QueryPerformanceFrequency(&li))
			return false;

		m_pcFreq = double(li.QuadPart);	// seconds
		QueryPerformanceCounter(&li);
		m_counterStart = li.QuadPart;
		return true;	
	}
	void finish()
	{ 
		LARGE_INTEGER li;
		QueryPerformanceCounter(&li);
		m_duration = double(li.QuadPart-m_counterStart)/m_pcFreq;
	}

	double duration() {
		return m_duration;
	}

	bool finished(){
		return m_counterStart==0;
	}
	
	char* to_string()
	{
		if(!finished())
			finish();
		sprintf(m_str, "%.6f (sec)", m_duration);		
		return m_str;
	}
};

#endif