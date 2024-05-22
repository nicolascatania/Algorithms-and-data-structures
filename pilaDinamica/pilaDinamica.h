
typedef struct sNodo{

    void* info;
    unsigned tamInfo;
    struct sNodo* sig;

}tNodo;

typedef tNodo* tPila;