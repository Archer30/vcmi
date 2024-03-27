/*
 * GlobalLobbyWindow.h, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#pragma once

#include "../windows/CWindowObject.h"

class GlobalLobbyWidget;
struct GlobalLobbyAccount;
struct GlobalLobbyRoom;

class GlobalLobbyWindow : public CWindowObject
{
	std::string chatHistory;

	std::shared_ptr<GlobalLobbyWidget> widget;

public:
	GlobalLobbyWindow();

	void doSendChatMessage();
	void doCreateGameRoom();

	void doInviteAccount(const std::string & accountID);
	void doJoinRoom(const std::string & roomID);

	void onGameChatMessage(const std::string & sender, const std::string & message, const std::string & when);
	void onActiveAccounts(const std::vector<GlobalLobbyAccount> & accounts);
	void onActiveRooms(const std::vector<GlobalLobbyRoom> & rooms);
	void onJoinedRoom();
	void onLeftRoom();
};
