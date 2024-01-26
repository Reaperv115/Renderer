#pragma once



namespace glitc
{
	struct MousePoint
	{
		int x;
		int y;
	};

	class MouseEvent
	{
	public:
		enum EventType
		{
			LPress,
			RPress,
			LRelease,
			RRelease,
			MPress,
			MRelease,
			WheelUp,
			WheelDown,
			Move,
			RAW_MOVE,
			Invalid
		};
	public:
		MouseEvent();
		MouseEvent(EventType type, int x, int y);
		MousePoint GetPos() const;
		int GetPosX() const;
		int GetPosY() const;
	private:
		EventType type;
		int x, y;
	};
}

