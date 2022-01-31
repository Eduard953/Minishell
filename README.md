# minishell
Minishell 42 Project from ebeiline and pstengl

## Prerequisites:
Install readline (if not already installed)
```bash
sudo apt install readline-common libreadline-dev
```

## Notes:
- Check Path start with:
    - `/` -> absolute Path
    - `.` -> relative Path
    - a character -> check in PATH
    - else nothing found
- Total lines of code: `TOTAL=0; for file in $(find . -maxdepth 1 -type f -name "*.c" -or -name "*.h"); do TOTAL=$(($TOTAL + $(cat $file | wc -l))); done; echo $TOTAL`

## TODO:
- fix export/unset memory issues
    if envp is freed and replaced, no other function seems to care and still uses the old envp (which is freed, thus producing errors)



- Fix literally 1 million leaks
- Fix exactly 228 norm errors (`norminette | grep -v OK | wc -l`)
