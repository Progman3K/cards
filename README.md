# cards


Use the cards via the command line

Builds for Windows, Linux and embedded

## Getting started

cards can be used to

- Play poker


## Usage

cards
 [debug level]

To display all debug messages:
```
cards -1
```


Examples:

```
```

## General remarks



## Build remarks

To build, go to the toplevel folder and choose which version, ex:

Build the 32-bit Windows version:
```
imake -DBUILD_WIN32 -DUseInstalled -I/usr/lib64/X11/config
make
```

Build the 64-bit Windows version:
```
imake -DBUILD_WIN64 -DUseInstalled -I/usr/lib64/X11/config
make
```

Build the console-mode version for all platforms:
```
xmkmf
make
```
