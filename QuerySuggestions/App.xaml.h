#pragma once

#include "App.xaml.g.h"

namespace winrt::QuerySuggestions::implementation
{
struct App : AppT<App>
{
    App();

    void OnLaunched(LaunchActivatedEventArgs const &);

  private:
    Window window{nullptr};
};
} // namespace winrt::QuerySuggestions::implementation
