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
	private:
		double LastTime;
		double CurrentTime;
		double DeltaTime;
		double PausedTime;

		bool IsPaused = false;
		bool StartedFromPaused = false;
		};
}