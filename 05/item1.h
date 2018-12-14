typedef char *Key;
struct record {
	Key keyVal;
	int value;
};
typedef struct record *Item;

#define maxN 1000
#define maxKey 100
#define NULLitem NULL
#define key(itemx) itemx->keyVal
