# DynCall

This library of functions is an useful proof of concept which allows one
to call any __fastcall function on a 64 bit environment dynamically.

User case: This was build to be used by (to be released) GTALua3. When doing reverse engineering of an application, or modding a
program or anything, we may need to call a function we see on IDA without having to leave the program (game) and recompile.
DynCall allows us to do it.

The source code has a few use examples.
