#pragma once

namespace Rhine
{
	class Timer
	{
	public:
		Timer();

		float GameTime() const;
		float DeltaTime() const;
		float TotalTime() const;
		

		void Reset();
		void Start();
		void Stop();
		void Tick();
	private:
		double secondsperCount;
		double deltaTime;

		__int64 baseTime;
		__int64 pauseTime;
		__int64 stopTime;
		__int64 prevTime;
		__int64 mcurrTime;

		bool stopped;
	};
}

