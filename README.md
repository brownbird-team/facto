# Facto calculator

This is a simple factorial calculator. You can build this program using GNU make,
just `cd` into project directory and run `make` command. To do this on debian based
systems, you need to install `build-essential` pakage. The compiled program will
be saved in build folder inside the project directory. Below are the commands that
can be used to build and start the program.

```bash
$ sudo apt update
$ sudo apt install build-essential
$ cd /path/to/project/falco
$ make
$ build/falco
```

Falco supports 3 modes in which it can calculate factorials.

- **normal**
  This is default mode. Calculation of factorial is preformed using long double variables and a for loop. This is the fastest way to calculate small factorials. But just like with stirling mode, size of factorial is limited

- **precise**
  In this mode our small bigint library is used to calculate value of factorial. Library is very basic and only supports a few operations, but this allows us to calculate factorial of any size. By default this mode is limited to factorial of 1000000 but you can extend this limit if you need.

- **stirling mode**
  In this mode program uses stirling's formula to calculate aproximation of factorial. Since double variables are used, size of the factorial is limited.

When you start the program type `help` to get the list of all available commands.

If you find any bugs or you have any questions feel free to contact us. Good luck :)
