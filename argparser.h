#define TYPE_FLAG 0
#define TYPE_STR 1
#define TYPE_STR_ALPHANUM 2
#define TYPE_STR_ALPHA_UPPER 3
#define TYPE_STR_ALPHA_LOWER 4
#define TYPE_STR_ALPHA 5
#define TYPE_INT 6
#define TYPE_CHAR 7

typedef struct {
	char args;
	char *desc;
	int type;
	int passed : 1;
	union {
		char chr;
		char *str;
		int integer;
	} value;
	int invalid : 1;
} Argument;

void parse_args(int, char*[], Argument*[], int);