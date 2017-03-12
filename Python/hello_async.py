#!/usr/bin/python3
import time
import asyncio
import sys

def current_millis():
    return int(round(time.time() * 1000))

async def hello():
    starttime = current_millis()

    while True:
        print("Hello")
        # Work for 5 seconds
        if current_millis() - starttime > 5000:
            break
        await asyncio.sleep(1)

    return "Done!"

# Create event loop
if sys.platform == "win32":
    loop = asyncio.ProactorEventLoop()
    asyncio.set_event_loop(loop)
else:
    loop = asyncio.get_event_loop()

value = loop.run_until_complete(hello())
print(value)
