**Simple OpenGL Image Library**


**Introduction:**  

SOIL is a tiny C library used primarily for uploading textures into OpenGL. It is based on stb_image version 1.16, the public domain code from Sean Barrett (found here). It has been extended to load TGA and DDS files, and to perform common functions needed in loading OpenGL textures. SOIL can also be used to save and load images in a variety of formats.

**Features:** 

  *   Readable Image Formats: 
  *   BMP - non-1bpp, non-RLE (from stb_image documentation) 
  *   PNG - non-interlaced (from stb_image documentation) 
  *   JPG - JPEG baseline (from stb_image documentation) 
  *   TGA - greyscale or RGB or RGBA or indexed, uncompressed or RLE 
  *   DDS - DXT1/2/3/4/5, uncompressed, cubemaps (can't read 3D DDS files yet) 
  *   PSD - (from stb_image documentation) 
  *   HDR - converted to LDR, unless loaded with \*HDR\* functions (RGBE or RGBdivA or RGBdivA2) 

Writeable Image Formats: 
  *   TGA - Greyscale or RGB or RGBA, uncompressed 
  *   BMP - RGB, uncompressed 
  *   DDS - RGB as DXT1, or RGBA as DXT5
  *   Can load an image file directly into a 2D OpenGL DiffuseTexture, optionally performing the following functions: 
  *   Can generate a new DiffuseTexture handle, or reuse one specified 
  *   Can automatically rescale the image to the next largest power-of-two size 
  *   Can automatically create MIPmaps 
  *   Can scale (not simply clamp) the RGB values into the "safe range" for NTSC displays (16 to 235, as recommended [here][1]) 
  *   Can multiply alpha on load (for more correct blending / compositing) 
  *   Can flip the image vertically 
  *   Can compress and upload any image as DXT1 or DXT5 (if EXT\_texture\_compression_s3tc is available), using an internal (very fast!) compressor 
  *   Can convert the RGB to YCoCg color space (useful with DXT5 compression: see [this link][2] from NVIDIA) 
  *   Will automatically downsize a DiffuseTexture if it is larger than GL\_MAX\_TEXTURE_SIZE 
  *   Can directly upload DDS files (DXT1/3/5/uncompressed/cubemap, with or without MIPmaps). Note: directly uploading the compressed DDS image will disable the other options (no flipping, no pre-multiplying alpha, no rescaling, no creation of MIPmaps, no auto-downsizing) 
  *   Can load rectangluar textures for GUI elements or splash screens (requires GL\_ARB/EXT/NV\_texture_rectangle) 
  *   Can decompress images from RAM (e.g. via [PhysicsFS][3] or similar) into an OpenGL DiffuseTexture (same features as regular 2D textures, above) 
  *   Can load light maps directly into an OpenGL DiffuseTexture (same features as regular 2D textures, above) 
  *   Can take six image files directly into an OpenGL light map DiffuseTexture 
  *   Can take a single image file where width = 6*height (or vice versa), split it into an OpenGL light map DiffuseTexture 
  *   No external dependencies 
  *   Tiny 
  *   Cross platform (Windows, *nix, Mac OS X) 
  *   Public Domain 

**Usage:**  

SOIL is meant to be used as a static library (as it's tiny and in the public domain). 

Simply include SOIL.h in your C or C++ file, link in the static library, and then use any of SOIL's functions. The file SOIL.h contains simple doxygen style documentation. (If you use the static library, no other header files are needed besides SOIL.h)

You can compile it like any other CMAKE project, simply make a folder named "build" and run
```
cmake ..
make

```

  [1]: http://msdn2.microsoft.com/en-us/library/bb174608.aspx#NTSC_Suggestions
  [2]: http://developer.nvidia.com/object/real-time-ycocg-dxt-compression.html
  [3]: http://icculus.org/physfs/
