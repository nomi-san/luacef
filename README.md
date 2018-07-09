<p align="center">
	<a href="https://github.com/wy3/luacef">
		<img src="https://github.com/wy3/luacef/raw/master/lcf.png" alt="" width="215px">
	</a>
	<h1 align="center"> LuaCEF </h1>
	<p align="center">
    	<strong> Chromium Embedded Framework for Lua. </strong>
 	</p>
</p>

-- __todo__

### How to store pointer?

```js
	lua:newuuserdata <- alloc [4-byte]
	~~~~~~~~~~~~~~~~
	       v
		<ptr**> -> <ptr*> = <udata*> <- alloc [n-byte]
	       |                   |---> ::free
	       v                   |---> ::set, get
	    <self**>  <------------|      ~~~~~~~~
		~~~~~~~~                          ^
		   |                               \
		   v                             ~~~~~~~~~
	[method, property] <- <metatable> -> reference
	       |
		   v
	     return

	  __LUA_side__
```

#### Example

```lua
-- require library
cef = require("luacef")

-- new main args, app
local args, app = cef.newMainArgs(), cef.newApp()

-- execute process and check, not necessary
local code = cef.ExecuteProcess(args, app)
if (code >= 0) then os.exit() end

-- new cef settings
local settings = cef.newSettings {
	single_process = 1; -- Lua interpreter cannot run multipl-process
						-- must set to 0 for self-running (independent executable program)
	log_severity = 99;	-- disable debug log file				
}

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

-- new client, with life span handler
local client = cef.newClient {
	LifeSpanHandler = life_span;
}

-- url string
local url = 'https://www.google.com/'

-- create browser window
cef.CreateBrowser(window_info, client, url, browser_settings) 

-- run message loop
-- in cef settings, if multi_threaded_message_loop = 1, must use window message loop
cef.RunMessageLoop()

-- shutdown
cef.Shutdown()

-- release object
-- not necessary, it has __gc method
client:release()
app:release()
life_span:release()
```

