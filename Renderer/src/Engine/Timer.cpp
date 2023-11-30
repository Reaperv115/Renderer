#include "trpch.h"
#include "Timer.h"

Rhine::Timer::Timer()
{
	__int64 countsperSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsperSec);
	secondsperCount = 1.0 / (double)countsperSec;
}

void Rhine::Timer::Tick()
{
	if (stopped)
	{
		deltaTime = 0.0;
		return;
	}

	// get the time this frame
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	mcurrTime = currTime;

	// time difference between this frame and the previous
	deltaTime = (mcurrTime - prevTime) * secondsperCount;

	// prepare for next frame
	prevTime = mcurrTime;

	if (deltaTime < 0.0)
		deltaTime = 0.0;
}

float Rhine::Timer::DeltaTime() const 
{
	return deltaTime;
}

void Rhine::Timer::Reset()
{
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

	baseTime = currTime;
	prevTime = currTime;
	stopTime = 0;
	stopped = false;
}

void Rhine::Timer::Stop()
{
	// if we are already stopped, then do nothing
	if (!stopped)
	{
		__int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

		// otherwise, save the time we stopped at
		// and set the boolean flag indicating
		// the timer has stopped
		stopTime = currTime;
		stopped = true;
	}
}

void Rhine::Timer::Start()
{
	__int64 startTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&startTime);

	// if we are resuming from a stopped state
	if (stopped)
	{
		// accumulate paused time
		pauseTime += (startTime - stopTime);

		// since we are starting the timer back up, the current
		// previous time is not valid, as it occurred while paused.
		// so reset it to the current time.
		prevTime = startTime;

		// no longer stopped
		stopTime = 0;
		stopped = false;
	}
}

float Rhine::Timer::TotalTime() const
{
	if (stopped)
	{
		return (((stopTime - pauseTime) - baseTime) * secondsperCount);
	}
	else
	{
		return (((mcurrTime - pauseTime) - baseTime) * secondsperCount);
	}
}
