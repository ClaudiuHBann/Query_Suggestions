#include "pch.h"

#include "Command.h"

#include "Command.g.cpp"

namespace winrt::QuerySuggestions::implementation
{
Command::Command(hstring const &aName, hstring const &aDescription) : mName(aName), mDescription(aDescription)
{
}
} // namespace winrt::QuerySuggestions::implementation
