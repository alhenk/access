access
======

Access Control with RFID reader DEMO-CR95HF-A
VID=0x0483,PID=0xd0d0

The project is based on:
hidapi-0.7.0.zip
https://github.com/signal11/hidapi/downloads


To build project:

1) check the environment variable JAVA_HOME

   echo $JAVA_HOME

   JAVA_HOME=/usr/lib/jvm/java-7-openjdk-amd64/
   
   if the value isn't actual, correct it (in my case java-7-openjdk-i386).

   export JAVA_HOME=/usr/lib/jvm/java-7-openjdk-i386/

2) compile Cr95hf.java

   cd cr95hf

   javac Cr95hf.java

3) generate header Cr95hf.h for C hid API native interface

   javah -jni Cr95hf.java

4) check the prototype consistency of native functions in C source and 
   the above automatically generated header

5) compile C sourse to get library file libCr95hf.so

   cd jni/hid

   make -C linux

6) run java project

   cd cr95hf

   sudo java -Djava.library.path=. Cr95hf


