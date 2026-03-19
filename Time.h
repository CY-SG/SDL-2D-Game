#pragma once
class Time {
public:
	virtual void Tick() = 0;
	virtual float DeltaTime() = 0;
	virtual ~Time() = default;
protected:
	float delta;
};