# DynCall

This is a class I developed to allow for calling any __\_\_fastcall__ function on a X64 environment.
The idea is to have the call arguments built in memory prior to making the call, this way the called function prototype doesn't need to be statically compiled.

Use case: This class was used on (yet to be released) GTALua3, to call in-game functions wihout having to predefine their prototypes, and therefore allow to call different functions from Lua while researching them on IDA or any other decompiler, without having to leave the game and recompile the GTALua3 code.

This can be used also to make calls to functions from Assembly, for example, or from any other language than Lua.

The usage is very simple:
* First create a calling context by doing:<br>
    ```
    DynCallContext ctx;
* Then initialize the calling context with the address of the function to call:<br>
    ```
    ctx.Init(SomeFunction);
* At this point, add all the arguments in order:<br>
    ```
    ctx.Push(arg1);
    ctx.Push(arg2);
    ctx.Push(arg3);
* Then make the call:<br>
    ```
    int result = ctx.Call<int>();
If enough care is taken to pass the correct argument order, types and number, the function will be called as if it was done like:<br>
    ```
    int result = SomeFunction(arg1, arg2, arg3);
    ```

The DynCall.cpp file contains a few usage examples.

If you like this project, and feels like helping me out with my music, please check:<br>
http://GoFundMe.com/make-analog-music-great-again/

