gcc -Wall -Wextra -g -o game main.c menu.c player.c ranking.c roulette/roulette.c roulette/setbet.c roulette/start_bet.c russian/russian.c

if errorlevel 1 (
    echo Pelotudo
    pause
    exit /b 1
)

pause
game.exe