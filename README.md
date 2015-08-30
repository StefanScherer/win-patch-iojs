# win-patch-iojs
[![Build status](https://ci.appveyor.com/api/projects/status/xac75j3av0cwpq47?svg=true)](https://ci.appveyor.com/project/StefanScherer/win-patch-iojs)

Windows tool to monkey-patch the iojs.exe to run in Windows Docker container.

This tools is only used as long as [docker/docker#15889](https://github.com/docker/docker/issues/15889) and [nodejs/node#2578](https://github.com/nodejs/node/issues/2578) or anything in Windows 2016 and Docker solves the problem to lookup IP addresses with the AI_ADDRCONFIG flag set.
