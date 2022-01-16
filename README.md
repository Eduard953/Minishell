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
    - a character -> check in PATH and local folder for executable
    - else nothing found

## TODO:
- Own Environment
- Execute the Commands
- Build the actual redirection pipes
- Build the builtins
- error management
- << Redirection
- >> Redirection
- $?
- Fix literally 4 million leaks
- Fix 16 thousand norm errors
