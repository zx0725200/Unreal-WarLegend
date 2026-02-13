#pragma once

class Enum
{
public:
	
};

UENUM(Blueprintable)
enum class EUserWidgetType : uint8
{
	None,
	Slot,
	Hud,
	Popup,
	Screen,
};