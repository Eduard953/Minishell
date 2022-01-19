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

## TODO:
- Own Environment // gets handled by builtins
- Build the builtins // Only `export` and `unset`
- Build the actual redirection pipes
- << Redirection
- '>> Redirection
- $?
- error management



- Fix literally 4 million leaks
- Fix 16 thousand norm errors
