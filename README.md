# NumConv
NumConv is simple tool for converting numbers from decimal numeral system to any other positional numeral system. The tool can work with any text and will convert every number in it to the corresponding numeral system. The tool can detect both integer numbers, decimal numbers and numbers in scientific form.
## How to use it
The tool can simply be runned by opening the cmd in the folder the executable is stored, and typing the command ```NumConv```. The application would wait for the user to enter a text, ending with new line and EOF symbol, and would print the converted text. Several options can be used in the command line to customize the conversion:
* ```-i``` – specifies input file. If input file is specified, the application will not wait for user input. The file must exist on the specified location.
* ```-o``` – specifies output file. If output file is specified, the application will not write the text on the console. If the file does not exist, it would be created.
* ```-b``` – specifies numeral system base. The number must be between 2 and 36 (including). Digits with decimal value bigger than 9 will be represented by lowercase latin letters. Should not be specified if ```-B``` or ```-d``` are already specified.
* ```-B``` – specifies numeral system base. The number must be between 2 and 36 (including). Digits with decimal value bigger than 9 will be represented by uppercase latin letters. Should not be specified if ```-d``` or ```-b``` are already specified.
* ```-d``` – specifies custom digit set for the numeral system. Must have at least 2 characters. The base of the system is determined by the size of the set and, unlike in options ```-b``` and ```-B```, can be bigger than 36. Should not be specified if ```-b``` or ```-B``` are already specified.
* ```-p``` – specifies the maximum number of symbols in the fractional part of the numbers. Must be non-negative integer.
### Default conversion settings
* Base: ```16```
* Digit set: ```0123456789ABCDEF```
* Precision: ```10```

Executing the application without specifying options is equivalent to executing one of the following commands:

```NumConv -p 10 -B 16```

```NumConv -p 10 -d 0123456789ABCDEF```
### Errors and warnings
The application would throw an error and would not convert the text if:
* there is a parameter without corresponding value.
* the input file cannot be reached or does not exist.
* the specified base is not a number or is smaller than 2 or bigger than 36.
* the size of the digit set is smaller than 2.
* the precision is not a number or is a negative number.
* the output file exists but cannot be opened.

The application would message a warning but will convert the text if:
* there are multiple specifications of ```-i```, ```-o``` or ```-p``` options. In that case the last specified value for each option would be used.
* there are more than one specifications of ```-b```, ```-B``` and ```-d``` options. In that case the last specified value for any of the options determines the base and digits of the numeral system.
