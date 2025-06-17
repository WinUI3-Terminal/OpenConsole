#pragma once
#include <unknwn.h>

typedef struct CONSOLE_PORTABLE_ATTACH_MSG {
  DWORD IdLowPart;
  LONG IdHighPart;
  ULONG64 Process;
  ULONG64 Object;
  ULONG Function;
  ULONG InputSize;
  ULONG OutputSize;
} CONSOLE_PORTABLE_ATTACH_MSG;

typedef CONSOLE_PORTABLE_ATTACH_MSG *PCONSOLE_PORTABLE_ATTACH_MSG;
typedef const CONSOLE_PORTABLE_ATTACH_MSG *PCCONSOLE_PORTABLE_ATTACH_MSG;

struct __declspec(uuid("E686C757-9A35-4A1C-B3CE-0BCC8B5C69F4")) IConsoleHandoff
    : ::IUnknown {
  virtual HRESULT __stdcall EstablishHandoff(HANDLE server, HANDLE inputEvent,
                                             PCCONSOLE_PORTABLE_ATTACH_MSG msg,
                                             HANDLE signalPipe,
                                             HANDLE inboxProcess,
                                             HANDLE *process) = 0;
};

struct __declspec(uuid(
    "746E6BC0-AB05-4E38-AB14-71E86763141F")) IDefaultTerminalMarker
    : ::IUnknown {};