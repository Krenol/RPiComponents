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

rpicomponents::KeyState rpicomponents::Key::GetState() const
{
	return keyState_.load();
}

bool rpicomponents::Key::IsChanged() const
{
	return stateChanged_.load();
}


