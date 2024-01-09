This is a snake game.
you know collect food and grow. 
![](https://github.com/LuEklund/Snake-SFML/blob/master/assets/thumbnail.png)

## Prerequisites

* Windows 10/11
* Visual Studio 2022
* SFML 2.6.x


## Installing

Clone the repository:
```bash
git clone https://github.com/LuEklund/1D-Combat-SFML.git
```
* Open the solution file.
When the project is open in Visual Studio
* Right-click on the project (Default) -> (Properties) -> (C/C++) -> (General) and add in "Additional Includes Directories" the path to your SFML includes directory.
* Now go to (Linker) -> (General) and add in "Additional Libray Directories" the path to your SFML Library directory.
* Finally in (Linker) -> (Input) add "sfml-main.lib;sfml-audio-d.lib;sfml-graphics-d.lib;sfml-network-d.lib;sfml-window-d.lib;sfml-system-d.lib;" in the begining of the section.


## Keybindings
Key | action
--- | ---
`A` | Move left.  
`W` | Move up.  
`S` | Move down.  
`D` | Spawn right. 
`ESC` | Pause the program.
