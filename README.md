<img align="left" src="https://github.com/wy3/luacef/raw/master/lcf.png?raw=true" width="150px">
<h1>LuaCEF</h1>
<p>
    Lua bindings to Chromium Embedded Framework
    <br>
    <img src="https://img.shields.io/badge/lua-5.1+-brightgreen.svg">
    <img src="https://img.shields.io/badge/cef-3.3112/chr60-blue.svg">
</p>

<br>

### Platforms
- [x] Windows
- [x] Linux
- [ ] Mac OS

### Features
- Use native code like C (CEF APIs)
- Support object oriented like C++
- Easy to use
- High performance

### Builds

#### CEF pre-built 3.3112

 Binaries type| Windows | Linux
--|--|--
Standard dist | [x86](http://opensource.spotify.com/cefbuilds/cef_binary_3.3112.1659.gfef43e0_windows32.tar.bz2) / [x64](http://opensource.spotify.com/cefbuilds/cef_binary_3.3112.1659.gfef43e0_windows64.tar.bz2) | [x86](http://opensource.spotify.com/cefbuilds/cef_binary_3.3112.1659.gfef43e0_linux32.tar.bz2) / [x64](http://opensource.spotify.com/cefbuilds/cef_binary_3.3112.1659.gfef43e0_linux64.tar.bz2)
Minimal dist | [x86](http://opensource.spotify.com/cefbuilds/cef_binary_3.3112.1659.gfef43e0_windows32_minimal.tar.bz2) / [x64](http://opensource.spotify.com/cefbuilds/cef_binary_3.3112.1659.gfef43e0_windows64_minimal.tar.bz2) | [x86](http://opensource.spotify.com/cefbuilds/cef_binary_3.3112.1659.gfef43e0_linux32_minimal.tar.bz2) / [x64](http://opensource.spotify.com/cefbuilds/cef_binary_3.3112.1659.gfef43e0_linux64_minimal.tar.bz2)
Sample app | [x86](http://opensource.spotify.com/cefbuilds/cef_binary_3.3112.1659.gfef43e0_windows32_client.tar.bz2) / [x64](http://opensource.spotify.com/cefbuilds/cef_binary_3.3112.1659.gfef43e0_windows64_client.tar.bz2) | [x86](http://opensource.spotify.com/cefbuilds/cef_binary_3.3112.1659.gfef43e0_linux32_client.tar.bz2) / [x64](http://opensource.spotify.com/cefbuilds/cef_binary_3.3112.1659.gfef43e0_linux64_client.tar.bz2)

#### Windows (gcc)
- Copy `libcef.lib` from `$(cef_dist)/release/` to `$(project)/deps/cef/`
- Build `Lua` (you can build from `$(project)/deps/lua/src/` with `make mingw`), rename static library (`.lib -> lua53.lib`, `.a -> liblua53.a`) and put it into `$(project)/deps/lua/`
- Run `$ lua build.lua`

#### Linux (gcc x64)

```bash
git clone https://github.com/wy3/luacef.git
cd luacef
curl http://opensource.spotify.com/cefbuilds/cef_binary_3.3112.1659.gfef43e0_linux64_minimal.tar.bz2 --output cef_minimal.tar.bz2
tar jfx cef_minimal.tar.bz2
mv cef_binary_3.3112.1659.gfef43e0_linux64_minimal cef_minimal
lua build.lua
```

### CEF's udata wrapper

```
----- C ----------------
lua:newuserdata  <- alloc
~~~~~~~~~~~~~~~
       |
       v
     heap[1] -> [0] := cef_type <- alloc
       |                   |---> :: free
       v                   |---> :: set/get
     self //  <------------|        ~~~~~~~
    ~~~~~~~~               v          ^^^
       |           <type properties>    \
       v                   v         ~~~~~~~~~
[method, property] <- <metatable> -> reference
       |
       v
----- LUA --------------
```

### Simple Google example

Notes: this example must be run via terminal, do not press Ctrl+B on Sublime Text.
```
$ lua example.lua
```

```lua
local cef = require("luacef")

-- new CefMainArgs, CefApp
local args, app = cef.newMainArgs(), cef.newApp() 

-- print version
cef.printv()

-- new CefSettings
local settings = cef.newSettings {
    log_severity = 99;  -- disable debug log and log file       
    single_process = 1; -- must set single-process for Lua command line 
}

-- enable high DPI support
cef.EnableHighDPISupport()

-- initialize application
local code = cef.Initialize(args, settings, app)
if (code == 0) then os.exit() end

-- create CefWindowInfo
local window_info = cef.newWindowInfo {
    -- set window name
    window_name = "Hello - LuaCEF"; -- Lua string be convert to cef string, accept unicode
    style = 0x10cf0000
}

-- create CefBrowserSettings for creating browser
local browser_settings = cef.newBrowserSettings()

-- create CefLifeSpanHandler
local life_span = cef.newLifeSpanHandler {
    -- implement OnAfterCreated callback function
    OnAfterCreated = function(self, browser) -- event
        print("-- on after created --")
        print(self, browser) --> CefLifeSpanHandler: <addr>, Browser: <addr>
        print('Window handle: ', browser:GetHost():GetWindowHandle())
    end;
}

-- implement OnBeforeClose with other way
function life_span:OnBeforeClose(browser)
    print("-- on before close --")
    -- test browser's method
    print('can go back:', browser:CanGoBack())
    print('can go forward:', browser:CanGoForward())
    -- quit cef messgae loop
    cef.QuitMessageLoop()
end;

-- CefKeyboardHandler
keyboard = cef.newKeyboardHandler {
    -- pre-key event
    OnPreKeyEvent = function(self, browser, event, os_event, is_keyboard_shortcut)
        if event.type == 2 then -- test release key
            if event.windows_key_code == 0xd then
                print('Enter key released')
            elseif event.windows_key_code == 0x1b then
                print('ESC key released')
            end
        end
        return 0
    end;
}

-- new CefClient
local client = cef.newClient {
    -- register CefLifeSpanHandler
    GetLifeSpanHandler = function(self) 
        return life_span
    end;
    -- register CefKeyboardHandler
    GetKeyboardHandler = function(self)
        return keyboard
    end;
}

-- url, native lua string
local url = 'https://www.google.com/'

-- create browser window
cef.CreateBrowser(window_info, client, url, browser_settings, nil)

-- run message loop
-- in cef settings, if multi_threaded_message_loop is true (1), must use window message loop
cef.RunMessageLoop()

-- shutdown
cef.Shutdown()
```

<p align="center">
<img src="https://i.imgur.com/GAro1wL.png">
</p>
