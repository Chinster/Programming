#!/usr/bin/python3
import time
import asyncio
import sys

@asyncio.coroutine
def create_stream(callback):
    process = yield from asyncio.create_subprocess_exec('./fake.sh',
                                             #"--no-uintput",
                                             #"--detach-kernel-driver"],
                                             stdout=asyncio.subprocess.PIPE)

    while True:
        line = yield from process.stdout.readline()
        if line:
            callback(line)
        else:
            break

    return process

if sys.platform == "win32":
    loop = asyncio.ProactorEventLoop()
    asyncio.set_event_loop(loop)
else:
    loop = asyncio.get_event_loop()

loop.run_until_complete(create_stream(lambda x: print("%s" % x)))
loop.close()

