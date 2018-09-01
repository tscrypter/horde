# Cyber Horde

## Getting the Project
1) Install [Unreal Engine 4.20](https://www.unrealengine.com/en-US/download).  (Assume engine is installed at `E:\Engines\UE_4.20`  
2) Get the code.  (Assume doing this in `E:\UnrealProjects`)  
   - `git clone git@github.com:scrypter/cyberhorde.git`

## Running from powershell  
Assumming that the UE4.20 engine is located at `E:\Engines\UE_4.20\Engine\Binaries\Win64\UE4Editor.exe` and this project is cloned to `"E:\UnrealProjects\CyberHorde`.  

1) To run just the game connected to Steam (Steam must already be running):  
    - `&"E:\Engines\UE_4.20\Engine\Binaries\Win64\UE4Editor.exe" "E:\UnrealProjects\CyberHorde\CyberHorde.uproject" -game`  

2) To run the game with logging and connected to Steam (Steam must already be running):
	- `&"E:\Engines\UE_4.20\Engine\Binaries\Win64\UE4Editor.exe" "E:\UnrealProjects\CyberHorde\CyberHorde.uproject" -game -log`  

3) To run the game without Steam:
	- `&"E:\Engines\UE_4.20\Engine\Binaries\Win64\UE4Editor.exe" "E:\UnrealProjects\CyberHorde\CyberHorde.uproject" -game -nosteam`

## Styleguides

### Git Commit Messages

* Use the present tense ("Add feature" not "Added feature")
* Use the imperative mood ("Move cursor to..." not "Moves cursor to...")
* Limit the first line to 72 characters or less
* Reference issues and pull requests liberally after the first line
* When only changing documentation, include `[ci skip]` in the commit title
* Consider starting the commit message with an applicable emoji:
    * :art: `:art:` when improving the format/structure of the code
    * :racehorse: `:racehorse:` when improving performance
    * :non-potable_water: `:non-potable_water:` when plugging memory leaks
    * :memo: `:memo:` when writing docs
    * :penguin: `:penguin:` when fixing something on Linux
    * :apple: `:apple:` when fixing something on macOS
    * :checkered_flag: `:checkered_flag:` when fixing something on Windows
    * :bug: `:bug:` when fixing a bug
    * :fire: `:fire:` when removing code or files
    * :green_heart: `:green_heart:` when fixing the CI build
    * :white_check_mark: `:white_check_mark:` when adding tests
    * :lock: `:lock:` when dealing with security
    * :arrow_up: `:arrow_up:` when upgrading dependencies
    * :arrow_down: `:arrow_down:` when downgrading dependencies
    * :shirt: `:shirt:` when removing linter warnings