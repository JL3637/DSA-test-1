@ECHO OFF

for /l %%i in (0 1 99) do (
    a < nonogram\%%i.in > output
    fc nonogram\%%i.out output
)