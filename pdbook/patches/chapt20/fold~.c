#include "m_pd.h"

static t_class *fold_class;

typedef struct _fold{
    t_object x_obj;
    float x_f;
} t_fold;

static t_int *fold_perform(t_int *w){
    t_float *in = (t_float *)(w[1]);
    t_float *out = (t_float *)(w[2]);
    int n = (int)(w[3]);
    while(n--){
        float f = *(in++);
        if(f > 1.0){
            f = 1.0 - (f- 1.0);
        }
        if(f < -1.0){
            f = -1.0 - (f + 1.0);
        }
        *out++ = f;
    }
    return (w+4);
}

static void fold_dsp(t_fold *x, t_signal **sp){
    dsp_add(fold_perform, 3, sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
}

static void *fold_new(void){
    t_fold *x = (t_fold *)pd_new(fold_class);
    outlet_new(&x->x_obj, gensym("signal"));
    return (void *)x;
}

void fold_tilde_setup(void){
    fold_class = class_new(gensym("fold~"),
        (t_newmethod)fold_new,
        0, sizeof(t_fold), CLASS_DEFAULT, 0);
    CLASS_MAINSIGNALIN(fold_class, t_fold, x_f);
    class_addmethod(fold_class, (t_method)fold_dsp, gensym("dsp"), 0);
}
