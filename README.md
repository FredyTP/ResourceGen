# ResourceGen
Generate Resource Files path in code

ResourceGen is a lightweight script for generation of code that contains an structure with the data of all files in the proyect.

IT ONLY SUPPORTS OUTPUT FOR C++ and JAVA, BUT MORE LANGUAGES WILL BE ADDED SOON.

The script can be called with no arguments. Then it creates the code for the folder it is contained and the output is in the same folder.

The possible arguments are:
1. Language output: C++ -> "cpp", Java -> "java".
2. Aditional parameter: C++ -> none, Java ->package name.
3. The folder resources path.
4. The folder path which want to use as base for the relative paths.
5. The output folder path.

The arguments must be provided in order and the lasts ones are optional:

-Valid convinations are: none, 1, 12, 123, 1234,12345.

-Invalid convinations are: 2, 23, 13, etc.
