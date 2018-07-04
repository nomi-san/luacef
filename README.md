<p align="center">
	<a href="https://github.com/wy3">
		<img src="https://github.com/wy3/luacef/raw/master/lcf.png" alt="" width="215px">
	</a>
	<h1 align="center"> LuaCEF </h1>
	<p align="center">
    	<strong> Chromium Embedded Framework for Lua. </strong>
 	</p>
</p>

-- __todo__

#### Example

```lua

local cef = require("luacef") -- require library

local args, app = cef.newMainArgs(), cef.newApp() -- new main args, app

local code = cef.ExecuteProcess(args, app) -- check execute, not necessary
if (code >= 0) then os.exit() end

local settings = cef.newSettings {
	single_process = 1; -- in Lua command line, cannot run multiple process
}						-- should set to 0 for self-running (independent executable program)

code = cef.Initialize(args, settings, app) -- initialize
if (code == 0) then os.exit() end

local window_info = cef.newWindowInfo {
	window_name = "Hello World!"; -- set window name
}

local browser_settings = cef.newBrowserSettings()
local life_span = cef.newLifeSpanHandler { -- create life span handler
	OnAfterCreated = function(self, browser) -- event
		print("-- on after created --")
		cef.ShowBrowser(browser) -- show window
	end;
	OnBeforeClose = function(self, browser)
		print("-- on before close --")
		cef.QuitMessageLoop() -- quit cef messgae loop
	end;
}

local client = cef.newClient { -- new client
	LifeSpanHandler = life_span; -- add life span handler to client
}

local url = 'https://www.google.com/' -- url
cef.CreateBrowser(window_info, client, url, browser_settings) -- create browser

cef.RunMessageLoop()
cef.Shutdown()

cef.delete(client) -- clean

```

