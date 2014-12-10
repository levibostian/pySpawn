pySpawn
=======

Python library to create child processes and send STDIN and capture STDOUT 

You know how tedious it becomes to continuously type input into the keyboard
when you are just learning to program and your program is always asking you
to enter input?

You know when you are writing a bunch of scripts and as you debug them you
get sick and tired of always typing input into your keyboard when you should
instead be focusing on debugging your script?

**Welcome pySpawn.**

Create a text file with your input you would normally type in the keyboard
and tell pySpawn what script to run with which executable and that is it.

# Example uses
Run a Python3 script using input from inputFile.txt.
```
from pyspawn import spawn

spawn.run_input_file("/home/levi/fil.py", "python3", "inputFile.txt")
```
...or a list of strings as input instead of a file
```
from pyspawn import spawn

spawn.run_input_list("/home/levi/fil.py", "python3", ["levi"])
```

It does not stop with just Python. Give pySpawn whatever executable
you want and the input script and it does the rest. Here is Ruby.
```
from pyspawn import spawn

spawn.run_input_file("/home/levi/fil.rb, "ruby", "inputFile.txt")
```

# Demo

1. Your input text file is a newline separated file like this one below:
inputFile.txt
```
pySpawn is the best!
```
It is just a text file with some text in it.

2. Now lets create a script to run against pySpawn:
runMe.py
```
output = input("hello there, what is your name? ")
print("Your name is: " + output)
```

3. Now create a script with the following code in it:
```
from pyspawn import spawn

output = spawn.run_input_file("runMe.py", "python3", "inputFile.txt")
print("Your program sent as output: " + output)
```

WOW! Now if you are debugging runMe.py for example in the future, just run
this script and that is it. Go focus on what's more important then typing
on your keyboard.