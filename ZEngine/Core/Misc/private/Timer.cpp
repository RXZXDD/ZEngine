#include "../public/Timer.h"

#include <chrono>
ZEngine::ZTimer::ZTimer()
{
	LastTime = std::chrono::duration<double>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
	CurrentTime = LastTime;
	DeltaTime = 0.0;
	PausedTime = 0.0;
}

void ZEngine::ZTimer::Start()
{
	if (IsPaused) {
		IsPaused = false;
		StartedFromPaused = true;
	}
}

void ZEngine::ZTimer::Pause()
{
	if (!IsPaused)
	{
		PausedTime = std::chrono::duration<double>(std::chrono::steady_clock::now().time_since_epoch()).count();
		IsPaused = true;
	}
}

void ZEngine::ZTimer::Update()
{
	if (!IsPaused)
	{
		LastTime = CurrentTime;
		CurrentTime = std::chrono::duration<double>(std::chrono::steady_clock::now().time_since_epoch()).count();
		if (StartedFromPaused) {
			DeltaTime = CurrentTime - LastTime - PausedTime;
			StartedFromPaused = false;
		} else {
			DeltaTime = CurrentTime - LastTime;
		}
	}
}

float ZEngine::ZTimer::GetDeltaTime() const
{
	return (float)DeltaTime;
}
