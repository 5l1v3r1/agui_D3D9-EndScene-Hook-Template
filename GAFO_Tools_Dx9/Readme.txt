https://guidedhacking.com/threads/dx9-image-class.7620/

Step by Step Usage:

-Normal Picture (for byte array, normal file in folder is common sense with given functions)
1) Get wished Picture into PNG Format
2) Open ImageToByteArray.exe
3) Enter the filename for the header e.g. gfx_picture and the array name: e.g. picture
4) Click Convert and add the header file to your Project
5) Add the following code

- Animations:
1) Use GifToFrames.exe to Convert the gif to an png
2) Use ImageToByteArray.exe to Convert to an header as above ...
3) Include all .. Create Object
4) Imprortant: InitImageS with the size of the png file which you got from the gif in point 1)
5) And in the Rendering you have two options

//I think 50 ms are perfect for animations, but try as you like 