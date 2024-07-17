
#include "btree.h"


typedef struct
{
    int identity;
    int age;
    char name[31];
    char surname[31];
    char nationality[31];
}dsPerson;

typedef struct
{
    int identity;
    int register_number;
}dsPersonIdx;

int createBatch();
int showBatch();
int createIdx();
int make_binary_search_tree(dsBinaryTree* p, const char* file_name);
int _make_bin_search_tree(dsBinaryTree* p, int inf_limit, int sup_limit, FILE* pf);
void printPerson(void** data, unsigned* dsize, const void* stream, const void* param)
{
    dsPerson* a = *(dsPerson**)data;
    fprintf((FILE*)stream, "%04d %03d %-30s %-30s %-30s\n", a->identity, a->age, a->surname, a->name, a->nationality);
}


void printPerson_idx(void** data, unsigned* dsize, const void* stream, const void* param)
{
        dsPersonIdx* a = *(dsPersonIdx**)data;
        fprintf((FILE*)stream, "ID: %04d REG: %03d\n", a->identity, a->register_number);
}

void printPerson_to_idx(void** data, unsigned* dsize, const void* stream, const void* param)
{
    dsPersonIdx* a = *(dsPersonIdx**)data;
    fwrite(a, sizeof(dsPersonIdx),1, (FILE*)stream);
}

int cmpIdentityIdx(const void* a, const void* b)
{
    dsPersonIdx* aa = (dsPersonIdx*)a;
    dsPersonIdx* bb = (dsPersonIdx*)b;

    return aa->identity - bb->identity;
}


int cmpIdentity(const void* a, const void* b)
{
    dsPerson* aa = (dsPerson*)a;
    dsPerson* bb = (dsPerson*)b;

    return aa->identity - bb->identity;
}

int main()
{
    dsBinaryTree tree_fixed, tree_variable;

    if(!createBatch())
    {
        puts("Error creating batch");
    }

    if(!createIdx())
    {
        puts("Error creating idx");
    }

    create_binary_tree(&tree_fixed);
    create_binary_tree(&tree_variable);


    puts("Tree created from an index created from a fixed length txt file");
    load_from_sorted_bin_file(&tree_fixed, "Files/index1.idx", sizeof(dsPersonIdx), read_from_bin);
    inorder(&tree_fixed, stdout, NULL, printPerson_idx);
    puts("Tree created from an index created from a variable length txt file");
    load_from_sorted_bin_file(&tree_variable, "Files/index2.idx", sizeof(dsPersonIdx), read_from_bin);
    inorder(&tree_variable, stdout, NULL, printPerson_idx);

    puts("Status of variable tree");
    if(is_complete_binary_tree(&tree_variable))
    {
        puts("COMPLETE");
    }
    else if(is_balanced_binary_tree(&tree_variable))
    {
        puts("BALANCED");
    }
    else if(is_avl_binary_tree(&tree_variable))
    {
        puts("AVL");
    }
    else
    {
        puts("UNBALANCED");
    }


    puts("Status of fixed tree");
    if(is_complete_binary_tree(&tree_fixed))
    {
        puts("COMPLETE");
    }
    else if(is_balanced_binary_tree(&tree_fixed))
    {
        puts("BALANCED");
    }
    else if(is_avl_binary_tree(&tree_fixed))
    {
        puts("AVL");
    }
    else
    {
        puts("UNBALANCED");
    }

    destroy_binary_tree(&tree_fixed);
    destroy_binary_tree(&tree_variable);

    return 0;
}



int createBatch()
{
        dsPerson people[] = {
        {121, 25, "John", "Smith", "American"},
        {322, 30, "Jane", "Doe", "Canadian"},
        {23, 22, "Alice", "Johnson", "British"},
        {45, 28, "Bob", "Williams", "Australian"},
        {51, 35, "Charlie", "Jones", "German"},
        {6, 40, "Diana", "Brown", "French"},
        {7, 45, "Eve", "Davis", "Spanish"},
        {8, 50, "Frank", "Miller", "Italian"},
        {92, 55, "Grace", "Wilson", "Mexican"},
        {10, 60, "Hank", "Moore", "Brazilian"},
        {11, 23, "Emily", "Taylor", "American"},
        {12, 27, "James", "Anderson", "Canadian"},
        {123, 32, "Oliver", "Thomas", "British"},
        {14, 29, "Sophia", "Jackson", "Australian"},
        {15, 33, "Liam", "White", "German"},
        {1446, 36, "Emma", "Harris", "French"},
        {1767, 42, "Noah", "Martin", "Spanish"},
        {128, 48, "Ava", "Thompson", "Italian"},
        {19, 53, "Isabella", "Garcia", "Mexican"},
        {201, 58, "Mason", "Martinez", "Brazilian"}
    };
    FILE* pf = fopen("Files/batch.txt", "wt");
    FILE* pf2 = fopen("Files/batch2.txt","wt");
    //using both fixed and variable length for practice purposes.
    if(!pf || !pf2)
    {
        return 0;
    }
    for(int i =0; i< sizeof(people)/sizeof(people[0]);i++)
    {
        fprintf(pf, "%d|%d|%s|%s|%s\n", people[i].identity,people[i].age,people[i].surname,people[i].name,people[i].nationality);
        fprintf(pf2, "%04d %03d %-30s %-30s %-30s\n", people[i].identity,people[i].age,people[i].surname,people[i].name,people[i].nationality);
    }

    fclose(pf);
    fclose(pf2);
    return 1;

}

int createIdx()
{
    int reg_n= 0;
    dsBinaryTree aux1, aux2;
    dsPerson buffer;
    dsPersonIdx person_index;
    FILE* pf = fopen("Files/batch.txt", "rt");
    FILE* pf2 = fopen("Files/batch2.txt", "rt");
    FILE* ipf = fopen("Files/index1.idx", "wb");
    FILE* ipf2= fopen("Files/index2.idx", "wb");

    if(!pf)
    {
        fclose(pf2);
        fclose(ipf);
        fclose(ipf2);
        return 0;
    }
    if(!pf2)
    {
        fclose(pf);
        fclose(ipf);
        fclose(ipf2);
        return 0;
    }
    create_binary_tree(&aux1);
    create_binary_tree(&aux2);

    while(fscanf(pf,"%d|%d|%[^|]|%[^|]|%[^\n]\n", &buffer.identity, &buffer.age, buffer.surname, buffer.name, buffer.nationality)!=EOF)
    {
        person_index.identity = buffer.identity;
        person_index.register_number = reg_n;

        append_iterative(&aux1, &person_index, sizeof(person_index),cmpIdentityIdx);

        reg_n++;
    }

    reg_n = 0;

    while(fscanf(pf2,"%d %d %30s %30s %30s\n", &buffer.identity, &buffer.age, buffer.surname, buffer.name, buffer.nationality)==5)
    {
        person_index.identity = buffer.identity;
        person_index.register_number = reg_n;

        append_iterative(&aux2, &person_index, sizeof(person_index),cmpIdentityIdx);

        reg_n++;
    }
    fclose(pf);
    fclose(pf2);

    //variable
    inorder(&aux1, ipf, NULL, printPerson_to_idx);
    //fixed
    inorder(&aux2, ipf2, NULL, printPerson_to_idx);


    fclose(ipf);
    fclose(ipf2);

    destroy_binary_tree(&aux1);
    destroy_binary_tree(&aux2);

    return 1;
}

