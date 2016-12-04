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

extern struct node_data *tempNode;
extern struct node_data *tempNode1;
extern struct node_data *tempNode2;
extern struct dc_node_data dc_node;
extern int *pointer_unique_vol;
