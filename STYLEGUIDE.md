### Indentation
Tabs for indentation, and no vertical alignment.

### Classes
```cpp
class FooBar
{
	...
};
```
### Functions and Methods
```cpp
// Functions
void fooBar()
{
	...
}
// Methods
void FooBar::fooBar()
{
	...
}
```
### Variables
```cpp
// Stack variables
FooBar fooBar;
// Pointers
FooBar* fooBar;
// Member variables
object.fooBar_; // Classes
object.fooBar; // Structs
```
### Macros
```cpp
#define FOO_BAR ...
#define FOO(BAR) ...
```

### Line width
Max 80 character. If a parameter list must be split, fill the first line as far as possible. And indent the next line one time.
```cpp
LRESULT CALLBACK Window::wndProc(HWND hwnd, UINT message, WPARAM wparam,
    LPARAM lparam)
{
	...
}
```
