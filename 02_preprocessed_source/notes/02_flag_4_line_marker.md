# Closer look at the line marker `4` flag... 
This one is worth slowing down for because it touches **linkage**, not really preprocessing itself.  
  
First, this:
```C++
# 1 "/usr/include/stdc-predef.h" 1 3 4
```
has flag `4`, which GCC documents as meaning the following... 
> Text should be treated as being in an implicit `extern "C"` block.  
  
To understand this, we need to understand what `extern "C"` means.  
  
### **Start with ordinary C++**
Suppose we write:
```C++
void foo(int x)
{
}
```
C++ supports things like function overloading:
```C++
void foo(int);
void foo(double);
void foo(const char*);
```
So the linker can't identify all three functions simply as `foo`. The compiler encodes type information into the symbol name. This is commonly called **name mangling**.  
  
On GCC, for example:
```C++
void foo(int);
```
might correspond to a symbol resembling:
```C++
_Z3fooi
```
The exact mangling scheme is ABI-specific(Application Binary Interface-how seprately compiled binary code agrees to work together), but the important point is:
```text
C++ source name
    │
    ▼
foo(int)
    │
    │ C++ linkage / mangling
    ▼
_Z3fooi
```
### **Now introduce C**
C doesn't have, C++ style function overloading. A C library might export a function whose symbol is simply like:
```C
foo
```
Now imaging C++ code declares it as ordinary C++:
```C++
void foo(int);
```
The C++ compiler could expect a mangled C++ symbol:
```text
_Z3fooi
``` 
while the C object file actually provides:
```text
foo
```
At link time:
```text
C library                       C++ code

provides:                       expects:

   foo                          _Z3fooi
    │                              │
    └──────────── X ───────────────┘

             names don't match
```
That's a problem!!!
### **Enter `extern "C"`  
C++ gives us a language linkage specification:
```C++
extern "C"{
    void foo(int);
}
```
This tells the C++ compiler that declarations have **C language linkage**.  
  
Conceptually:
```text
extern "C"
     │
     ▼
Don't treat this declaration as
an ordinary C++ linkage declaration.
Use C language linkage.
```
A very common header pattern is therefore:
```C++ 
#ifdef __cplusplus
extern "C"{
#endif

void foo(int);
void bar(double);

#ifdef __cplusplus
}
#endif
```
Why the *`#ifdef`*?  
  
Because:
```C++
extern "C"
```
is C++ **syntax**. A *`C compiler`* doesn't understand it.  
  
But, C++ compilers normally define:
```C++
__cplusplus
```
So the same header can work in both languages.  
  
### **Now back to our mysterious** `4`
GCC produced:
```C++
# 1 "/usr/include/stdc-predef.h" 1 3 4
```
You can roughly read those flags as:
```text
1 -> entering a new file
3 -> this is a system header
4 -> implicit extern "C"
```
That last flag communicates information to later compile stages equivalent in spirit to:
> Treat apprapriate declarations originating from this region as having **C language** linkage, even though you don't literally see an **`extern "C"{ ... }`** written into the preprocessor output.  
  
That's why we use the word **implicit**.  
  
The marker:
```C++
... 4
```
is *metadata communicating the linkage context.  
  
#### **One important correction/nuance**  
  
It's tempting to reduce:
```C++
extern "C"
```
to:
> "Turn of name mangling."  
  
That's a useful first approximation, but it's not the formal definition.  
  
More accurately:
> `extern "C"` specifies **C language linkage** for the declarations involved.  
  
How that affects symbol naming is implementation/ABI territory. On the GCC/Linux systems you're experimenting with, the visible consequence you'll often notice is the difference between *C++ mangled symbols* and *C-style symbols*.  
  
And... since we're are studying the compilation model, we can actually prove this instead of taking my word for it.  
  
We can make:
```C++
void cpp_function(int){}

extern "C" void c_function(int){}
```
then, compile it to a .o file, and then use:  
```Bash 
nm
```
to inspect the actual symbols GCC generated.  
  
That would connect `extern "C"` directly to the object-file/linking stage, which I think would fit nicely with where our notes are heading. 
