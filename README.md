# Launch unreal engine's .uasset diff from perforce
This tool will ask a running instance of Unreal Engine to [show a diff](https://docs.unrealengine.com/5.2/en-US/ue-diff-tool-in-unreal-engine/) between two version of the same asset. This process can be run from Perforce when doing a diff between files.

You should be able to see the diff screen within 1 second after asking for it from P4V.

![blueprint diff](doc/diff-bp.png?raw=true)

## Setup

### 1. Download the script

Click on the "Code" button and download the .zip of this repository. Only the `src` folder will be needed you can delete the rest.

![download](doc/download.png?raw=true)

### 2. Setup P4v

In P4v click in “Edit/Preferences”

![p4v prefences](doc/p4v-pref.png?raw=true)

Then in the “Diff” menu, click on “Add…”

![p4v edit diff](doc/p4v-edit-diff.png?raw=true)

It will open a window where you will specific the diff behavior. Unreal Engine is embedding python so simply need to point to it to be able to execute scripts. You will also need to copy the path to where you extracted the `src` folder as you will need it as argument.

**Extension** : `.uasset`

**Application** :  `YOUR_ENGINE_FOLDER/Engine/Binaries/ThirdParty/Python3/Win64/python.exe`

**Arguments** : `YOUR_PATH\src\unreal_diff_uassets.py %1 %2`

→ As arguments, it is important to use “\” instead of “/” in the path

![p4v edit diff](doc/p4v-edit-diff-done.png?raw=true)

### 3. Setup Unreal Engine

First you want to check that the “Python Editor Script Plugin” is enabled in your project

![ue-plugins](doc/ue-plugins.png?raw=true)

![ue-plugins](doc/ue-python.png?raw=true)

Then in the project settings, you want to make sure that “Enable Remote Execution” is enabled as well

![ue settings](doc/ue-settings.png?raw=true)

![ue settings](doc/ue-settings-python.png?raw=true)

## Usage

**You need to have Unreal Engine opened** for the script to work.

In perforce, simply open the history tab on an .uasset file, select a revision and right click to use the “Diff against previous revision”.

The diff command can also be run on many other windows, such as when you are checking a CL or using the revision graph.

## Troubleshooting

### Is the python script path correct ?

When the python script encounter an error, it will display a window such as the one below.

![cannot connect error](doc/cannot-connect.png?raw=true)

When running the diff on a `.uasset` from perforce, if no diff window shows up, and if you have no error message, then it is very likely that the path you entered in the "Setup P4v" part above is incorrect.
