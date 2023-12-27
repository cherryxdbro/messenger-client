#pragma once

enum class Pages
{
	Empty,
	ChatPage,
	ConnectionPage,
	MainPage,
	SettingsPage
};

Pages getPageByTag(winrt::hstring tag);
