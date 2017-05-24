#ifndef SYMTAB_H
#define SYMTAB_H

#define SYMTAB_HASH_SIZE 4096

typedef struct SYMTAB_ENTRY_s {
	struct SYMTAB_ENTRY_s * next;
	int  id;
	char name[1];
} SYMTAB_ENTRY;

typedef struct SYMTAB_s {
	int count;
	struct SYMTAB_ENTRY_s *entries[SYMTAB_HASH_SIZE];
} SYMTAB;

SYMTAB* symtab_create();
void    symtab_destroy(SYMTAB *);
int     symtab_insert(const char *, SYMTAB *, SYMTAB_ENTRY **);
int     symtab_lookup(const char *, SYMTAB *, SYMTAB_ENTRY **);
void    symtab_dump(SYMTAB *);

#endif