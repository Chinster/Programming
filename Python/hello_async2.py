#!/usr/bin/python3
import time
import asyncio
import sys

def current_millis():
    return int(round(time.time() * 1000))

async def hello(n):
    starttime = current_millis()

    while True:
        print("Hello")
        # Work for 5 seconds
        if current_millis() - starttime > 5000:
            break
        await asyncio.sleep(n)

    return "Done!"

# Create event loop
if sys.platform == "win32":
    loop = asyncio.ProactorEventLoop()
    asyncio.set_event_loop(loop)
else:
    loop = asyncio.get_event_loop()

tasks = [
    asyncio.ensure_future(hello(1)),
    asyncio.ensure_future(hello(2))
]

task = loop.create_task(hello(3))

val1, val2 = loop.run_until_complete(asyncio.gather(*tasks))

print(val1)
print(val2)
print(task.result())

loop.close()
