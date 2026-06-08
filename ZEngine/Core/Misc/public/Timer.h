#pragma once

namespace ZEngine
{
	class ZTimer
	{
	public:
		ZTimer();
		void Start();
		void Pause();
		void Update();

		float GetDeltaTime() const;
		float GetTotalTime() const;
	private:
		double LastTime;
		double CurrentTime;
		double DeltaTime;
		double PausedTime;

		double TotalTime;

		bool IsPaused = false;
		bool StartedFromPaused = false;
		};
}