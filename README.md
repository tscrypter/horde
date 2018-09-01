# Cyber Horde

## Getting the Project
1) Install [Unreal Engine 4.20](https://www.unrealengine.com/en-US/download). (Assume engine is installed at `E:\Engines\UE_4.20`  
2) Get the code (Assume doing this in `E:\UnrealProjects`. `git clone git@github.com:scrypter/cyberhorde.git`

## Running from powershell  
Assumming that the UE4.20 engine is located at `E:\Engines\UE_4.20\Engine\Binaries\Win64\UE4Editor.exe` and this project is cloned to `"E:\UnrealProjects\CyberHorde`.  

To run just the game connected to Steam (Steam must already be running):  
`&"E:\Engines\UE_4.20\Engine\Binaries\Win64\UE4Editor.exe" "E:\UnrealProjects\CyberHorde\CyberHorde.uproject" -game`  

To run the game with logging and connected to Steam (Steam must already be running):
`&"E:\Engines\UE_4.20\Engine\Binaries\Win64\UE4Editor.exe" "E:\UnrealProjects\CyberHorde\CyberHorde.uproject" -game -log`  

To run the game without Steam:
`&"E:\Engines\UE_4.20\Engine\Binaries\Win64\UE4Editor.exe" "E:\UnrealProjects\CyberHorde\CyberHorde.uproject" -game -nosteam`
