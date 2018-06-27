# luacef
Chromium Embedded Framework for Lua

-- __todo__

#### Example

```lua
cef = require("luacef")

args = cef.newMainArgs() -- new main args
app = cef.newApp() -- new app handler

code = cef.ExecuteProcess(args, app)
if (code >= 0) then os.exit() end -- check for execute

settings = cef.newSettings() -- new settings

cef.Initialize(args, settings, app) -- initialize

wininfo = cef.newWindowInfo { -- new window info
	window_name = "Hello World!";
}

bs = cef.newBrowserSettings() -- new browser settings

client = cef.newClient() -- new client handler

url = "https://google.com.vn" -- url

cef.CreateBrowser(wininfo, client, url, bs) -- create browser

cef.RunMessageLoop() -- run message loop
cef.Shutdown() -- shutdown
```
