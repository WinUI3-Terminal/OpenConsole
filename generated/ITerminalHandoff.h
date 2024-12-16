#pragma once
#include <unknwn.h>

typedef struct _TERMINAL_STARTUP_INFO
{
    // In STARTUPINFO
    BSTR pszTitle;

    // Also wanted
    BSTR pszIconPath;
    LONG iconIndex;

    // The rest of STARTUPINFO
    DWORD dwX;
    DWORD dwY;
    DWORD dwXSize;
    DWORD dwYSize;
    DWORD dwXCountChars;
    DWORD dwYCountChars;
    DWORD dwFillAttribute;
    DWORD dwFlags;
    WORD wShowWindow;
} TERMINAL_STARTUP_INFO;

// LOAD BEARING!
//
// There is only ever one OpenConsoleProxy.dll loaded by COM for _ALL_ terminal
// instances, across Dev, Preview, Stable, whatever. So we have to keep all old
// versions of interfaces in the file here, even if the old version is no longer
// in use.

// This was the original prototype. The reasons for changes to it are explained below.

struct __declspec(uuid("59D55CCE-FC8A-48B4-ACE8-0A9286C6557F")) ITerminalHandoff
    : ::IUnknown {
  virtual HRESULT __stdcall EstablishPtyHandoff(HANDLE in,
                                             HANDLE out,
                                             HANDLE signal,
                                             HANDLE ref,
                                             HANDLE server,
                                             HANDLE client) = 0;
};

// We didn't consider the need for TERMINAL_STARTUP_INFO, because Windows Terminal never had support for launching
// .lnk files in the first place. They aren't executables after all, but rather a shell thing.
// Its need quickly became apparent right after releasing ITerminalHandoff, which is why it was very short-lived.

struct __declspec(uuid("AA6B364F-4A50-4176-9002-0AE755E7B5EF")) ITerminalHandoff2
    : ::IUnknown {
  virtual HRESULT __stdcall EstablishPtyHandoff(HANDLE in,
                                             HANDLE out,
                                             HANDLE signal,
                                             HANDLE ref,
                                             HANDLE server,
                                             HANDLE client,
                                             TERMINAL_STARTUP_INFO startupInfo) = 0;
};

// Quite a while later, we realized that passing the in/out handles as [in] instead of [out] has always been flawed.
// It prevents the terminal from making choices over the pipe buffer size and whether to use overlapped IO or not.
// The other handles remain [in] parameters because they have always been created internally by ConPTY.
// Additionally, passing TERMINAL_STARTUP_INFO by-value was unusual under COM as structs are usually given by-ref.

struct __declspec(uuid("6F23DA90-15C5-4203-9DB0-64E73F1B1B00")) ITerminalHandoff3
    : ::IUnknown {
  virtual HRESULT __stdcall EstablishPtyHandoff(HANDLE in,
                                             HANDLE out,
                                             HANDLE signal,
                                             HANDLE reference,
                                             HANDLE server,
                                             HANDLE client,
                                             TERMINAL_STARTUP_INFO* startupInfo) = 0;
};

