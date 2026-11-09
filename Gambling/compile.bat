gcc -Wall -Wextra -g -o game main.c menu.c player.c roulette/roulette.c roulette/setbet.c roulette/start_bet.c

if errorlevel 1 (
    echo Pelotudo
    pause
    exit /b 1
)

pause
game.exe