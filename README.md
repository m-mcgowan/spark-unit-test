This is a port of the [Arduino Unit](https://github.com/mmurdoch/arduinounit) library to the spark. 
Please see that repo for library usage, or check out the examples.

Additions in the spark version:

- when running, the RGB led indicates the overall test health
- configuration at runtime of tests to include or exclude, via `cmd(include=pattern)`
- waits to run tests until either 't' is received over serial, or the Cloud `cmd` function is called with 'start'
- test stats (passed/failed/skipped/count) available as cloud variables 
- test running state (waiting, running, complete) available as a variable, 
and changes to running state are published as events.

These features are documented below.

RGB Led
-------

When the test suite app executes, it initially enters the waiting state. 
The RGB led shows the usual breathing cyan as the spark is connected to the cloud.

When the test suite is later started, the RGB led shows a solid color to reflect
the current test health:

 - green: all tests (so far) have passed
 - orange: some tests skipped but otherwise all passed
 - red: some tests failed

When the test suite has completed running, the LED status remains so you can leave the spark
running and come back when it's done to see the result.
(In future, the LED may blink while the tests are running, and then return to solid when all tests are done, 
to make it easy to see when the tests are still running or not.)


Including/Excluding Tests
-------------------------

Tests can be filtered at runtime using include/exclude globs. The include/exclude
feature is described in the [Arduino unit documentation](https://github.com/mmurdoch/arduinounit#selecting-tests).

To exclude tests ending "*_slow":

```
spark call mycore cmd exclude=*_slow
```

To run only tests starting with 'abc':

```
spark call mycore cmd exclude=*
spark call mycore cmd include=abc*
```


Starting the Test Suite
-----------------------
If the test code hasn't requested the test suite starts immediately, the test suite
will wait until:

- a 't' is sent over Serial, or
- the `cmd(start)` function is called.

E.g. to start the tests via the cloud:

 `spark call mycore cmd start`


Enter DFU Mode
--------------
As part of a locally operating automated tset suite, it can be useful to 
put the core in DFU mode for quick flashing of another app.

This is done with the command

 `spark call mycore cmd enterDFU`

On receiving the command, the core will reset and enter DFU mode (flashing yellow LED.)

Variables for Test Statistics
-----------------------------

The test suite exposes variables to the cloud to allow monitoring of the test health:

- count (int32): the number of tests to be run (available from startup)
- state (int32): the state of the test runner
 - 1: waiting to start running tests
 - 2: running - busy executing tests
 - 3: complete - all tests executed
- passed (int32): the number of tests passed so far.
- failed (int32): the number of tests failed so far.
- skipped (int32): the number of tests skipped so far.

These variables are updated as the test suite executes. 

Events
------

The test suite publishes events as the test runner state changes. This allows
external apps to monitor progress, e.g. wait for the test suite to complete.

The event `state` is published whenever the running state of the test suite changes. 
The event can have these values:

- waiting: waiting to start
- running: executing tests
- complete: all tests executed

(NB: it would be easy in code to add an event each time a test has been executed, however
this could easily generate too many events causing more important events, such as the
running state change 'complete', to be dropped.)





