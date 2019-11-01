#include "key.hpp"
#include "key.hpp"
#include "key.hpp"
#include "key.hpp"

rpicomponents::Key::Key() : Component(COMPONENT_KEY)
{
}

rpicomponents::Key::Key(const char& userChar) : Component(COMPONENT_KEY), userChar_{userChar}
{
}

rpicomponents::Key::Key(char&& userChar) : Component(COMPONENT_KEY), userChar_{ userChar }
{
}

rpicomponents::Key::Key(const Key& key) : Component(COMPONENT_KEY), userChar_{ key.GetChar() }
{
}

void rpicomponents::Key::UpdateKey(const char& userChar, const KeyState& userState, bool userStatus) const
{
	userChar_.store(userChar);
	keyState_.store(userState);
	stateChanged_.store(userStatus);
}

char rpicomponents::Key::GetChar() const
{
	return userChar_.load();
}

void rpicomponents::Key::SetChar(const char& userChar) const
{
	userChar_.store(userChar);
}

rpicomponents::KeyState rpicomponents::Key::GetState() const
{
	return keyState_.load();
}

void rpicomponents::Key::SetState(const KeyState& userState) const
{
	keyState_.store(userState);
}

bool rpicomponents::Key::IsChanged() const
{
	return stateChanged_.load();
}

void rpicomponents::Key::SetChanged(bool userStatus) const
{
	stateChanged_.store(userStatus);
}


