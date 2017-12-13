# C argument parser #
Simple argument parser written in and for c

It was / is being developed as a simple extension in university during programming classes.


## How to use ##
1. specify argument
```C
Argument arg_db = { 'd', "Database file", TYPE_STR };
```
2. combine arguments into array
```C
Argument *args[] = { &arg_db };
```
3. call argparser
```C
parse_args(argc, argv, args, 1);
```
4. Check if argument was passed and is valid
```C
if (arg_db.passed && !arg_db.invalid)
```
5. Access passed data
```C
arg_db.value.str
```

## Access passed data ##
- Character: `arg.value.chr`
- String: `arg.value.str`
- Integer: `arg.value.integer`

## Argument types ##
| type name | values |
| -- | :--:|
| TYPE_FLAG | Flag, only needs to be added |
| TYPE_STR  | a-zA-Z0-9!"#$%'()*+´-./:;<=>?@[\]^_`{|}~ |
| TYPE_STR_ALPHANUM | a-zA-Z0-9 |
| TYPE_STR_ALPHA_UPPER | A-Z |
| TYPE_STR_ALPHA_LOWER | a-z |
| TYPE_STR_ALPHA | a-zA-Z |
| TYPE_INT | Integer |
| TYPE_CHAR | single Character |

## TO DO ##
- add support for longer parameter names
- add support for strings with whitespaces