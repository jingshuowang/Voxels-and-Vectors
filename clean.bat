@echo off
REM Clean up build output and auto-generated folders/files in all subdirectories
del /s /q *.obj *.exe *.dll *.pdb *.cache *.log *.pri *.xbf *.winmd *.json *.resources.pri *.dat *.config *.appxrecipe
del /s /q *.csproj.nuget.* *.nuget.* *.intermediate *.user *.dbmdl *.bak *.old *.orig *.tmp
for /d %%d in (bin obj .vs .vscode TestResults) do if exist %%d rd /s /q %%d
