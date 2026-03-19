#pragma once
class Window {
public:
	virtual bool ShouldClose() const = 0;
	virtual void PollEvents() = 0;
	virtual ~Window() = default;
};