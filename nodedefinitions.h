struct node_data
{
    char element_type;
    int element_number;
    int ini_node;
    int fin_node;
    double element_value;
    struct node_data *nextnode;
};

struct dc_node_data
{
    int status;
    char dc_type;
    int dc_number;
    double start;
    double stop;
    double step;
};

int nnodes,nvoltages=0,nlines=0;
int *pointer_unique_vol=NULL;
struct dc_node_data dc_node;
struct node_data *node;
struct node_data *tempNode;
double **mna_matrix;
double **mna_matrix_z;
double *mna_matrix_x;
double **augmentedmatrix;
struct node_data *head = NULL;
struct node_data *hashtable[100] = {NULL};

