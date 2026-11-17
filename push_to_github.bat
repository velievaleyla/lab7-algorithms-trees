@echo off
chcp 65001 > nul
echo ========================================================
echo  Синхронізація репозиторію з GitHub (Велієва Л.А.)
echo ========================================================
echo.
set /p REPO_URL="Введіть посилання на ваш GitHub репозиторій (або натисніть Enter для https://github.com/velievaleyla/lab7-algorithms-trees.git): "
if "%REPO_URL%"=="" set REPO_URL=https://github.com/velievaleyla/lab7-algorithms-trees.git

echo Налаштування віддаленого репозиторію: %REPO_URL%
git remote remove origin 2>nul
git remote add origin %REPO_URL%
echo Відправка комітів на GitHub (гілка master)...
git branch -M master
git push -u origin master

if %ERRORLEVEL% equ 0 (
    echo.
    echo [УСПІХ] Проект успішно завантажено на GitHub!
) else (
    echo.
    echo [УВАГА] Не вдалося автоматично відправити.
    echo Перевірте, чи створено репозиторій на GitHub під цим посиланням, та чи виконано вхід.
)
pause
