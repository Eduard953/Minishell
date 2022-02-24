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
- Fix exactly 34 norm errors (`norminette | grep -v OK | wc -l`)
- Maybe fix some last memory leaks
- exit.c fix returncodes when error
- exit.c the handling of the error Code in our code for "external" commands up to the variable replacement is broken
- free memory after exit.c - maybe ebeiline
- Fix redirection pipes
- Fix ec"ho" behaviour
- export with no args: declare -x env
