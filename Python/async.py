#!/usr/bin/python3
import time
import asyncio
import sys

@asyncio.coroutine
def create_stream(callbacks):
    process = yield from asyncio.create_subprocess_exec('./fake.sh',
                                             #"--no-uintput",
                                             #"--detach-kernel-driver"],
                                             stdout=asyncio.subprocess.PIPE)

    while True:
        line = yield from process.stdout.readline()
        if line:
            for cb in callbacks:
                cb()
        else:
            break

    return process

def blocking():
    print("Handled")

def handler():
    print("Hi")

if sys.platform == "win32":
    loop = asyncio.ProactorEventLoop()
    asyncio.set_event_loop(loop)
else:
    loop = asyncio.get_event_loop()

handlers = [blocking, handler]
loop.run_until_complete(create_stream(handlers))
