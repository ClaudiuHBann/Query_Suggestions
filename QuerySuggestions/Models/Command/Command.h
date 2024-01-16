#pragma once

#include "Command.g.h"

namespace winrt::QuerySuggestions::implementation
{
struct Command : CommandT<Command>
{
    CREATE_PROPERTY_CHANGED_EVENTS;

  private:
    hstring mName{};
    hstring mDescription{};

  public:
    Command(hstring const &aName, hstring const &aDescription);

    METHOD_GET_PROPERTY(Name);
    METHOD_GET_PROPERTY(Description);
};
} // namespace winrt::QuerySuggestions::implementation

namespace winrt::QuerySuggestions::factory_implementation
{
struct Command : CommandT<Command, implementation::Command>
{
};
} // namespace winrt::QuerySuggestions::factory_implementation
