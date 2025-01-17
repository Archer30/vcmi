/*
* InputSourceMouse.cpp, part of VCMI engine
*
* Authors: listed in file AUTHORS in main folder
*
* License: GNU General Public License v2.0 or later
* Full text of license available in license.txt file, in main folder
*
*/

#include "StdInc.h"
#include "InputSourceMouse.h"
#include "InputHandler.h"

#include "../gui/CGuiHandler.h"
#include "../gui/EventDispatcher.h"
#include "../gui/MouseButton.h"

#include "../render/IScreenHandler.h"

#include "../../lib/Point.h"
#include "../../lib/CConfigHandler.h"

#include <SDL_events.h>
#include <SDL_hints.h>

InputSourceMouse::InputSourceMouse()
	:mouseToleranceDistance(settings["input"]["mouseToleranceDistance"].Integer())
{
	SDL_SetHint(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, "1");
}

void InputSourceMouse::handleEventMouseMotion(const SDL_MouseMotionEvent & motion)
{
	Point newPosition = Point(motion.x, motion.y) / GH.screenHandler().getScalingFactor();
	Point distance= Point(-motion.xrel, -motion.yrel) / GH.screenHandler().getScalingFactor();

	mouseButtonsMask = motion.state;

	if (mouseButtonsMask & SDL_BUTTON(SDL_BUTTON_MIDDLE))
		GH.events().dispatchGesturePanning(middleClickPosition, newPosition, distance);
	else if (mouseButtonsMask & SDL_BUTTON(SDL_BUTTON_LEFT))
		GH.events().dispatchMouseDragged(newPosition, distance);
	else
		GH.input().setCursorPosition(newPosition);
}

void InputSourceMouse::handleEventMouseButtonDown(const SDL_MouseButtonEvent & button)
{
	Point position = Point(button.x, button.y) / GH.screenHandler().getScalingFactor();

	switch(button.button)
	{
		case SDL_BUTTON_LEFT:
			if(button.clicks > 1)
				GH.events().dispatchMouseDoubleClick(position, mouseToleranceDistance);
			else
				GH.events().dispatchMouseLeftButtonPressed(position, mouseToleranceDistance);
			break;
		case SDL_BUTTON_RIGHT:
			GH.events().dispatchShowPopup(position, mouseToleranceDistance);
			break;
		case SDL_BUTTON_MIDDLE:
			middleClickPosition = position;
			GH.events().dispatchGesturePanningStarted(position);
			break;
	}
}

void InputSourceMouse::handleEventMouseWheel(const SDL_MouseWheelEvent & wheel)
{
	GH.events().dispatchMouseScrolled(Point(wheel.x, wheel.y) / GH.screenHandler().getScalingFactor(), GH.getCursorPosition());
}

void InputSourceMouse::handleEventMouseButtonUp(const SDL_MouseButtonEvent & button)
{
	Point position = Point(button.x, button.y) / GH.screenHandler().getScalingFactor();

	switch(button.button)
	{
		case SDL_BUTTON_LEFT:
			GH.events().dispatchMouseLeftButtonReleased(position, mouseToleranceDistance);
			break;
		case SDL_BUTTON_RIGHT:
			GH.events().dispatchClosePopup(position);
			break;
		case SDL_BUTTON_MIDDLE:
			GH.events().dispatchGesturePanningEnded(middleClickPosition, position);
			break;
	}
}
