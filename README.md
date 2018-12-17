<p align="center">
	<a href="https://github.com/wy3/luacef">
		<img src="https://github.com/wy3/luacef/raw/master/lcf.png" alt="" width="215px">
	</a>
	<h1 align="center"> LuaCEF </h1>
	<p align="center">
    	<strong> Chromium Embedded Framework for Lua. </strong>
	<br><br>
	<a href="https://travis-ci.org/wy3/luacef" target="_blank">
		<img src="https://travis-ci.org/wy3/luacef.svg?branch=master">
	</a>
	<br>
 	</p>
</p>

## >> __todo__ [32%]

### Based on
- [![image](https://img.shields.io/badge/lua-5.3.4-brightgreen.svg)](https://www.lua.org/ftp/)
- [![image](https://img.shields.io/badge/cef/chromium-3.3112/60-blue.svg)](http://opensource.spotify.com/cefbuilds/index.html)

### Platforms
- [x] Windows
- [x] Linux
- [ ] Mac OS

### Features
- Use native code like C
- Support object oriented like C++
- Easy to use
- High performance

### Build

#### CEF pre-built 3.3112

 Binaries type| Windows | Linux
--|--|--
Standard dist | [x86](http://opensource.spotify.com/cefbuilds/cef_binary_3.3112.1659.gfef43e0_windows32.tar.bz2) / [x64](http://opensource.spotify.com/cefbuilds/cef_binary_3.3112.1659.gfef43e0_windows64.tar.bz2) | [x86](http://opensource.spotify.com/cefbuilds/cef_binary_3.3112.1659.gfef43e0_linux32.tar.bz2) / [x64](http://opensource.spotify.com/cefbuilds/cef_binary_3.3112.1659.gfef43e0_linux64.tar.bz2)
Minimal dist | [x86](http://opensource.spotify.com/cefbuilds/cef_binary_3.3112.1659.gfef43e0_windows32_minimal.tar.bz2) / [x64](http://opensource.spotify.com/cefbuilds/cef_binary_3.3112.1659.gfef43e0_windows64_minimal.tar.bz2) | [x86](http://opensource.spotify.com/cefbuilds/cef_binary_3.3112.1659.gfef43e0_linux32_minimal.tar.bz2) / [x64](http://opensource.spotify.com/cefbuilds/cef_binary_3.3112.1659.gfef43e0_linux64_minimal.tar.bz2)
Sample app | [x86](http://opensource.spotify.com/cefbuilds/cef_binary_3.3112.1659.gfef43e0_windows32_client.tar.bz2) / [x64](http://opensource.spotify.com/cefbuilds/cef_binary_3.3112.1659.gfef43e0_windows64_client.tar.bz2) | [x86](http://opensource.spotify.com/cefbuilds/cef_binary_3.3112.1659.gfef43e0_linux32_client.tar.bz2) / [x64](http://opensource.spotify.com/cefbuilds/cef_binary_3.3112.1659.gfef43e0_linux64_client.tar.bz2)

#### Windows
- Copy `libcef.lib` from `$(cef_dist)/release/` to `$(project)/deps/cef/`
- Build `Lua` (you can build from `$(project)/deps/lua/src/` with `make mingw`), rename static library (`.lib -> lua53.lib`, `.a -> liblua53.a`) and put it to `$(project)/deps/lua/`
- Run `$ lua build.lua`

#### Linux (x64)

```bash
git clone https://github.com/wy3/luacef.git
cd luacef
curl http://opensource.spotify.com/cefbuilds/cef_binary_3.3112.1659.gfef43e0_linux64_minimal.tar.bz2 --output cef_minimal.tar.bz2
tar jfx cef_minimal.tar.bz2
mv cef_binary_3.3112.1659.gfef43e0_linux64_minimal cef_minimal
lua build.lua
```

....

### My technology for pointer :)

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

```lua
cef = require("luacef")

-- new main args, app
local args, app = cef.newMainArgs(), cef.newApp() 

-- execute process and check, not necessary
local code = cef.ExecuteProcess(args, app)
if (code >= 0) then os.exit() end

-- print version
cef.printv()

-- new cef settings
local settings = cef.newSettings {

    log_severity = 99;  -- disable debug log and log file       
    single_process = 1; -- must set single-process for Lua command line 
}

-- enable high DPI support, for windows 7 or newer
cef.EnableHighDPISupport()

-- initialize application
code = cef.Initialize(args, settings, app)
if (code == 0) then os.exit() end

-- create window info
local window_info = cef.newWindowInfo {

    -- set window name
    window_name = "Hello World!"; -- Lua string be convert to cef string, accept unicode
}

-- create browser settings for create browser
local browser_settings = cef.newBrowserSettings()

-- create life span handler
local life_span = cef.newLifeSpanHandler {

    -- implement OnAfterCreated callback function
    OnAfterCreated = function(self, browser) -- event
        print("-- on after created --")
        print(self, browser) --> LifeSpanHandler: <address>, Browser: <address>
        print('Window handle: ', browser:GetHost():GetWindowHandle())

        -- show browser window
        cef.ShowBrowser(browser, 10)
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

-- keyboard handler
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

-- new client
local client = cef.newClient {
    -- set life span handler by return it
    GetLifeSpanHandler = function(self) 
        return life_span
    end;
    -- set keyboard handler
    GetKeyboardHandler = function(self)
        return keyboard
    end;
}

-- url string
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
<img src="https://i.imgur.com/8mmTqjW.png" width="600">
</p>

<br>

### License [Apache 2.0](https://github.com/wy3/luacef/blob/master/LICENSE)

Copyright © 2018 by [__me__](https://github.com/wy3).

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at [here](http://www.apache.org/licenses/LICENSE-2.0).
   
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
