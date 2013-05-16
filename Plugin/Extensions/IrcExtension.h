/**
* John Bradley (jrb@turrettech.com)
*/
#pragma once

#include <string>
#include <vector>

extern "C" {
#include "libircclient.h"
}

#include "..\JavascriptExtension.h"

class IrcExtension :
	public JavascriptExtension
{

private:
	HANDLE hThread;
	irc_session_t *session;

	std::string nickName;
	std::string channelName;
	std::vector<std::string> messages;

	bool isJoinedChannel;

	CRITICAL_SECTION messageLock;

public:
	IrcExtension();
	virtual ~IrcExtension();

public:
	void AddMessage(std::string &string) {
		EnterCriticalSection(&messageLock);
		messages.push_back(string);
		LeaveCriticalSection(&messageLock);
	}

public:
	irc_session_t *GetSession() { return session; }

	std::string &GetChannelName() { return channelName; }

	std::string &GetNickName() { return nickName; }
	void SetNickName(std::string &nickName) { this->nickName = nickName; }

	bool IsJoinedChannel() { return isJoinedChannel; }
	void SetJoinedChannel(bool isJoinedChannel) { this->isJoinedChannel = isJoinedChannel; }

public:
	JSValue Handle(const std::string &functionName, const Awesomium::JSArray &args);
};

class IrcExtensionFactory : public JavascriptExtensionFactory
{

public:
	JavascriptExtension *Create() {
		return new IrcExtension();
	}
};