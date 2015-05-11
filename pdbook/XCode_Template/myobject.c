#include "m_pd.h"

static t_class *myobject_class;

typedef struct _myobject{
    t_object x_obj;
} t_myobject;

void *myobject_new(void){
    t_myobject *x = (t_myobject *)pd_new(myobject_class);
    post("Hello world !!");
    return (void *)x;
}

void myobject_setup(void){
    myobject_class = class_new(gensym("myobject"),
                               (t_newmethod)myobject_new, 0, sizeof(t_myobject),
                               CLASS_DEFAULT, 0);
}
