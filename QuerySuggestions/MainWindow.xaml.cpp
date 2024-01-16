#include "pch.h"

#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

static const inline vector<QuerySuggestions::Command> COMMANDS = {
    {L"ASSOC", L"Displays or modifies file extension associations."},
    {L"ATTRIB", L"Displays or changes file attributes."},
    {L"BREAK", L"Sets or clears extended CTRL + C checking."},
    {L"BCDEDIT", L"Sets properties in boot database to control boot loading."},
    {L"CACLS", L"Displays or modifies access control lists(ACLs) of files."},
    {L"CALL", L"Calls one batch program from another."},
    {L"CD", L"Displays the name of or changes the current directory."},
    {L"CHCP", L"Displays or sets the active code page number."},
    {L"CHDIR", L"Displays the name of or changes the current directory."},
    {L"CHKDSK", L"Checks a disk and displays a status report."},
    {L"CHKNTFS", L"Displays or modifies the checking of disk at boot time."},
    {L"CLS", L"Clears the screen."},
    {L"CMD", L"Starts a new instance of the Windows command interpreter."},
    {L"COLOR", L"Sets the default console foreground and background colors."},
    {L"COMP", L"Compares the contents of two files or sets of files."},
    {L"COMPACT", L"Displays or alters the compression of files on NTFS partitions."},
    {L"CONVERT", L"Converts FAT volumes to NTFS.You cannot convert the current drive."},
    {L"COPY", L"Copies one or more files to another location."},
    {L"DATE", L"Displays or sets the date."},
    {L"DEL", L"Deletes one or more files."},
    {L"DIR", L"Displays a list of files and subdirectories in a directory."},
    {L"DISKPART", L"Displays or configures Disk Partition properties."},
    {L"DOSKEY", L"Edits command lines, recalls Windows commands, and creates macros."},
    {L"DRIVERQUERY", L"Displays current device driver status and properties."},
    {L"ECHO", L"Displays messages, or turns command echoing on or off."},
    {L"ENDLOCAL", L"Ends localization of environment changes in a batch file."},
    {L"ERASE", L"Deletes one or more files."},
    {L"EXIT", L"Quits the CMD.EXE program(command interpreter)"},
    {L"FC", L"Compares two files or sets of files, and displays the differences between them."},
    {L"FIND", L"Searches for a text string in a file or files."},
    {L"FINDSTR", L"Searches for strings in files."},
    {L"FOR", L"Runs a specified command for each file in a set of files."},
    {L"FORMAT", L"Formats a disk for use with Windows."},
    {L"FSUTIL", L"Displays or configures the file system properties."},
    {L"FTYPE", L"Displays or modifies file types used in file extension associations."},
    {L"GOTO", L"Directs the Windows command interpreter to a labeled line in a batch program."},
    {L"GPRESULT", L"Displays Group Policy information for machine or user."},
    {L"GRAFTABL", L"Enables Windows to display an extended character set in graphics mode."},
    {L"HELP", L"Provides Help information for Windows commands."},
    {L"ICACLS", L"Display, modify, backup, or restore ACLs for files and directories."},
    {L"IF", L"Performs conditional processing in batch programs."},
    {L"LABEL", L"Creates, changes, or deletes the volume label of a disk."},
    {L"MD", L"Creates a directory."},
    {L"MKDIR", L"Creates a directory."},
    {L"MKLINK", L"Creates Symbolic Links and Hard L"},
    {L"MODE", L"Configures a system device."},
    {L"MORE", L"Displays output one screen at a time."},
    {L"MOVE", L"Moves one or more files from one directory to another directory."},
    {L"OPENFILES", L"Displays files opened by remote users for a file share."},
    {L"PATH", L"Displays or sets a search path for executable files."},
    {L"PAUSE", L"Suspends processing of a batch file and displays a message."},
    {L"POPD", L"Restores the previous value of the current directory saved by PUSHD."},
    {L"PRINT", L"Prints a text file."},
    {L"PROMPT", L"Changes the Windows command prompt."},
    {L"PUSHD", L"Saves the current directory then changes it."},
    {L"RD", L"Removes a directory."},
    {L"RECOVER", L"Recovers readable information from a bad or defective disk."},
    {L"REM", L"Records comments(remarks) in batch files or CONFIG.SYS."},
    {L"REN", L"Renames a file or files."},
    {L"RENAME", L"Renames a file or files."},
    {L"REPLACE", L"Replaces files."},
    {L"RMDIR", L"Removes a directory."},
    {L"ROBOCOPY", L"Advanced utility to copy files and directory t"},
    {L"SET", L"Displays, sets, or removes Windows environment variables."},
    {L"SETLOCAL", L"Begins localization of environment changes in a batch file."},
    {L"SC", L"Displays or configures services(background processes)"},
    {L"SCHTASKS", L"Schedules commands and programs to run on a computer."},
    {L"SHIFT", L"Shifts the position of replaceable parameters in batch files."},
    {L"SHUTDOWN", L"Allows proper local or remote shutdown of machine."},
    {L"SORT", L"Sorts input."},
    {L"START", L"Starts a separate window to run a specified program or command."},
    {L"SUBST", L"Associates a path with a drive letter."},
    {L"SYSTEMINFO", L"Displays machine specific properties and configuration."},
    {L"TASKLIST", L"Displays all currently running tasks including services."},
    {L"TASKKILL", L"Kill or stop a running process or application."},
    {L"TIME", L"Displays or sets the system time."},
    {L"TITLE", L"Sets the window title for a CMD.EXE session."},
    {L"TREE", L"Graphically displays the directory structure of a drive or path."},
    {L"TYPE", L"Displays the contents of a text file."},
    {L"VER", L"Displays the Windows version."},
    {L"VERIFY", L"Tells Windows whether to verify that your files are written correctly to a disk."},
    {L"VOL", L"Displays a disk volume label and serial number."},
    {L"XCOPY", L"Copies files and directory trees."},
    {L"WMIC", L"Displays WMI information inside interactive command shell."}};

static const inline vector<hstring> ALGORITHMS = {L"Levenshtein", L"Dice Coefficient"};

namespace winrt::QuerySuggestions::implementation
{
MainWindow::MainWindow()
    : mCommands(single_threaded_observable_vector<Command>()), mAlgorithms(single_threaded_observable_vector<hstring>())
{
    InitializeComponent();
    Title(L"Query Suggestions");

    mCommands.ReplaceAll(COMMANDS);
    mAlgorithms.ReplaceAll(ALGORITHMS);
}

static size_t Levenshtein(const wstring &aString1, const wstring &aString2) noexcept
{
    const auto string1Length = aString1.size(), string2Length = aString2.size();

    vector<vector<size_t>> cache(string1Length + 1, vector<size_t>(string2Length + 1, 0));

    for (size_t i = 1; i <= string1Length; i++)
    {
        cache[i][0] = i;
    }

    for (size_t i = 1; i <= string2Length; i++)
    {
        cache[0][i] = i;
    }

    for (size_t i = 1; i <= string1Length; i++)
    {
        for (size_t j = 1; j <= string2Length; j++)
        {
            cache[i][j] = std::min({cache[i - 1][j] + 1, cache[i][j - 1] + 1,
                                    cache[i - 1][j - 1] + static_cast<size_t>(aString1[i - 1] != aString2[j - 1])});
        }
    }

    return cache[string1Length][string2Length];
}

static double DiceCoefficient(const wstring &aString1, const wstring &aString2) noexcept
{
    set<wstring> string1Bigrams{}, string2Bigrams{};
    if (!aString1.length() || !aString2.length())
    {
        return 0.f;
    }

    for (size_t i = 0; i < aString1.length() - 1; i++)
    {
        string1Bigrams.insert(aString1.substr(i, 2));
    }

    for (size_t i = 0; i < aString2.length() - 1; i++)
    {
        string2Bigrams.insert(aString2.substr(i, 2));
    }

    auto intersection =
        accumulate(string2Bigrams.begin(), string2Bigrams.end(), 0.,
                   [&](const auto &aSum, const auto &aBiagram) { return aSum + string1Bigrams.count(aBiagram); });
    return intersection * 2. / (string1Bigrams.size() + string2Bigrams.size());
}

void MainWindow::OnTextChangedAutoSuggestBox(AutoSuggestBox const &aSender,
                                             AutoSuggestBoxTextChangedEventArgs const &aArgs)
{
    if (aArgs.Reason() != AutoSuggestionBoxTextChangeReason::UserInput)
    {
        return;
    }

    mCommands.Clear();

    wstring query(aSender.Text());
    if (query.empty())
    {
        mCommands.ReplaceAll(COMMANDS);
        return;
    }

    CharUpperW(query.data());
    for (const auto &command : COMMANDS)
    {
        wstring commandName(command.Name());
        CharUpperW(commandName.data());

        const auto algorithmName = algorithm().SelectedValue().as<hstring>();
        if (algorithmName == ALGORITHMS[0] && Levenshtein(query, commandName) > mLevenshteinOptimal)
        {
            continue;
        }
        else if (algorithmName == ALGORITHMS[1] && DiceCoefficient(query, commandName) < mDiceCoefficientOptimal)
        {
            continue;
        }

        mCommands.Append(command);
    }
}
} // namespace winrt::QuerySuggestions::implementation
