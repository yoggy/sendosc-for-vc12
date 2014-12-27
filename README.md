sendosc-for-vc12
====
sendosc is Open Sound Control packet sending program.

This program was compiled using Visual Studio 2013.

* https://github.com/yoggy/sendosc

Usage
====
<pre>
C:\>sendosc.exe
usage : sendosc dst_host dst_port path [[type] [param]] ...

  type
    i : int
    f : float
    b : boolean (true/false)
    s : string

  example
    ./sendosc 127.0.0.1 5678 /test1 i 123
    ./sendosc 127.0.0.1 5678 /test2 f 123.45
    ./sendosc 127.0.0.1 5678 /test3 s teststring
    ./sendosc 127.0.0.1 5678 /test4 b true
    ./sendosc 127.0.0.1 5678 /test5 s teststring i 123 f 123.4 b false

</pre>

Libraries
====
sendosc-for-vc12 uses the following libraries.

* liboscpack_1_1_0-vc12
  * https://github.com/yoggy/liboscpack_1_1_0-vc12
