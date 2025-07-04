# Dll Search Path Patcher
This is a simple dll to patch the DLL search path of a process. 

It will inline hook `version.dll` and call `SetDefaultDllDirectories` to set the DLL search path to `LOAD_LIBRARY_SEARCH_APPLICATION_DIR | LOAD_LIBRARY_SEARCH_SYSTEM32 | LOAD_LIBRARY_SEARCH_USER_DIRS`.

This will ignore dll search from PATH Environment Variable.