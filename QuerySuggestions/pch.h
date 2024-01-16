#pragma once

#ifndef NOMINMAX
#define NOMINMAX
#endif // !NOMINMAX

// win32
#include <unknwn.h>
// unknwn.h contains multiple libs which the lower
// libs are dependent on so unknwn.h needs to be first
#include <commctrl.h>
#pragma comment(lib, "Comctl32.lib")
#include <shellapi.h>
#pragma comment(lib, "Shell32.lib")

#undef GetCurrentTime

// microsoft
/*
    "Microsoft.UI.Xaml.Window.h" needs to be before "Windows.Foundation.h"
    because both contains IUnknown (IUnknown and winrt::Windows::Foundation::IUnknown)
    and we don't want winrt::Windows::Foundation::IUnknown to exist yet
*/
#include <Microsoft.UI.Xaml.Window.h>
#include <winrt/Microsoft.UI.Xaml.Controls.Primitives.h>
#include <winrt/Microsoft.UI.Xaml.Markup.h>
#include <winrt/Microsoft.Windows.AppLifecycle.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Data;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Microsoft::Windows::AppLifecycle;
using namespace Microsoft::UI::Xaml::Controls::Primitives;

// winrt
#include <winrt/Windows.ApplicationModel.Resources.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Foundation.h>

using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::ApplicationModel::Resources;

// std
#include <algorithm>
#include <chrono>
#include <filesystem>
#include <format>
#include <fstream>
#include <functional>
#include <iostream>
#include <limits>
#include <numeric>
#include <ranges>
#include <set>

using namespace std;
using namespace views;
using namespace ranges;
using namespace chrono;
using namespace filesystem;

/*
    !!! THE PROPERTY NEEDS TO BE ALREADY DEFINED !!!


    Creates a set method that updates the property with the new value if they are different.


    Example:

        METHOD_SET_PROPERTY(PropertyName) becomes:

        void PropertyName(decltype(mPropertyName) const & aValue)
        {
            if (mPropertyName != aValue)
            {
                mPropertyName = aValue;
            }
        }
   };
*/
#define METHOD_SET_PROPERTY(property)                                                                                  \
    void property(decltype(m##property) const &aValue)                                                                 \
    {                                                                                                                  \
        if (m##property != aValue)                                                                                     \
        {                                                                                                              \
            m##property = aValue;                                                                                      \
        }                                                                                                              \
    }

/*
    !!! THE PROPERTY NEEDS TO BE ALREADY DEFINED !!!


    Creates a get method that returns the property.


    Example:

        METHOD_GET_PROPERTY(PropertyName) becomes:

        decltype(mPropertyName) PropertyName()
        {
            return mPropertyName;
        }
   };
*/
#define METHOD_GET_PROPERTY(property)                                                                                  \
    decltype(m##property) property()                                                                                   \
    {                                                                                                                  \
        return m##property;                                                                                            \
    }

/*
    Creates the event property as "mEventPropertyChanged"
    Creates the methods of adding/removing handlers respectively tokens
*/
#define CREATE_PROPERTY_CHANGED_EVENTS                                                                                 \
  private:                                                                                                             \
    event<PropertyChangedEventHandler> mEventPropertyChanged;                                                          \
                                                                                                                       \
  public:                                                                                                              \
    event_token PropertyChanged(PropertyChangedEventHandler const &aHandler)                                           \
    {                                                                                                                  \
        return mEventPropertyChanged.add(aHandler);                                                                    \
    }                                                                                                                  \
                                                                                                                       \
    void PropertyChanged(event_token const &aToken) noexcept                                                           \
    {                                                                                                                  \
        mEventPropertyChanged.remove(aToken);                                                                          \
    }

/*
    !!! DEFINE "CREATE_PROPERTY_CHANGED_EVENTS" BEFORE USING !!!

    Extended version of METHOD_SET_PROPERTY define that signals that the property has been changed
*/
#define METHOD_SET_AND_SIGNAL_PROPERTY(property)                                                                       \
    void property(decltype(m##property) const &aValue)                                                                 \
    {                                                                                                                  \
        if (m##property != aValue)                                                                                     \
        {                                                                                                              \
            m##property = aValue;                                                                                      \
            mEventPropertyChanged(*this, PropertyChangedEventArgs(L## #property));                                     \
        }                                                                                                              \
    }

/*
    https://learn.microsoft.com/en-us/windows/uwp/app-resources/localize-strings-ui-manifest

    Loads a string as hstring from the Resources/en-US/Resources.resw strings by name
*/
#define LOAD_STRINGH(name)                                                                                             \
    ::winrt::Windows::ApplicationModel::Resources::ResourceLoader::GetForViewIndependentUse().GetString(name)

// Same as LOAD_STRINGH but loads the string as wstring
#define LOAD_STRING(name) wstring(LOAD_STRINGH(name).data())
