#include "pch.h"

#include "Pages.h"

Pages getPageByTag(winrt::hstring tag)
{
	if (tag == L"ChatPage")
	{
		return Pages::ChatPage;
	}
	else if (tag == L"ConnectionPage")
	{
		return Pages::ConnectionPage;
	}
	else if (tag == L"MainPage")
	{
		return Pages::MainPage;
	}
	else if (tag == L"SettingsPage")
	{
		return Pages::SettingsPage;
	}
	return Pages::Empty;
}
