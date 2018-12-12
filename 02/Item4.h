typedef char *Item;
#define LIMIT "LIMIT"
#define eq(x, y) (x != NULL && y != NULL && strcmp(x, y) == 0)
#define copy(x, y)                                                             \
	x = (char *)malloc((500) * sizeof(char));                                  \
	strcpy(x, y);
#define itemfree(x) free(x)
#define itemformat "%s"