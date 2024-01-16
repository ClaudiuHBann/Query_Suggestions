#pragma once

#include "MainWindow.g.h"

namespace winrt::QuerySuggestions::implementation
{
struct MainWindow : MainWindowT<MainWindow>
{
  private:
    IObservableVector<Command> mCommands{};
    IObservableVector<hstring> mAlgorithms{};

    size_t mLevenshteinOptimal = 2;
    double mDiceCoefficientOptimal = 0.25;

  public:
    MainWindow();

    void OnTextChangedAutoSuggestBox(AutoSuggestBox const &aSender, AutoSuggestBoxTextChangedEventArgs const &aArgs);

    METHOD_GET_PROPERTY(Commands);
    METHOD_GET_PROPERTY(Algorithms);
};
} // namespace winrt::QuerySuggestions::implementation

namespace winrt::QuerySuggestions::factory_implementation
{
struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
{
};
} // namespace winrt::QuerySuggestions::factory_implementation
