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
- error management



- Fix literally 5 million leaks
- Fix exactly 229 norm errors (`norminette | grep -v OK | wc -l`)
