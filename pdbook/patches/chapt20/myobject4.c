#include "m_pd.h"

static t_class *myobject_class;

typedef struct _myobject{
    t_object x_obj;
    t_outlet *x_outlet;
    float count;
} t_myobject;

void myobject_bang(t_myobject *x){
    outlet_float(x->x_outlet, x->count);
    x->count++;
}

void *myobject_new(void ){
    t_myobject *x = (t_myobject *)pd_new(myobject_class);
    x->x_outlet = outlet_new(&x->x_obj, gensym("float"));
    x->count = 0;
    return (void *)x;
}

void myobject_set(t_myobject *x, t_floatarg f){
    x->count = f;
}

void myobject_setup(void){
    myobject_class = class_new(gensym("myobject"),
        (t_newmethod)myobject_new, 0, sizeof(t_myobject),
        CLASS_DEFAULT, 0);
    class_addbang(myobject_class, myobject_bang);
    class_addmethod(myobject_class, (t_method)myobject_set,
        gensym("set"), A_FLOAT, 0);
}
