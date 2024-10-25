#include "fmod.h"
#include "quickjs.h"

static FMOD_SYSTEM *sys;

static JSValue js_dsp_copy(JSContext *js, JSValueConst self, int argc, JSValueConst *argv)
{
/*  audiobuffer to = js2audiobuffer(js, argv[0]);
  audiobuffer from = js2audiobuffer(js, argv[1]);
  int offset;
  JS_ToInt32(js, &offset, argv[2]);

  int frames_remaining = from.frames - offset;
  if (frames_remaining <=0 ) return JS_UNDEFINED;
  
//  if (to.channels != from.channels || to.samplerate != from.samplerate) return JS_EXCEPTION;
  int frames = (frames_remaining < to.frames) ? frames_remaining : to.frames;
  
  float *fromf = from.data;
  float *tof = to.data;
  
  if (to.channels != from.channels)
    dsp_mono(to, from, offset);
  else
    memcpy(to.data, BUFFERPOS(from,offset), BUFFERSIZE(to));

  return JS_NewInt32(js, offset+frames);*/
}

static const JSCFunctionListEntry js_fmod_funcs[] = {
//  JS_CFUNC_DEF("copy", 3, js_dsp_copy),
};

#define INITCLASS(TYPE) \
JS_NewClassID(&js_##TYPE##_class_id); \
JS_NewClass(JS_GetRuntime(js), js_##TYPE##_class_id, &js_##TYPE##_class); \
JSValue TYPE##_proto = JS_NewObject(js); \
JS_SetPropertyFunctionList(js, TYPE##_proto, js_##TYPE##_funcs, countof(js_##TYPE##_funcs)); \
JS_SetClassProto(js, js_##TYPE##_class_id, TYPE##_proto); \

static int js_fmod_init(JSContext *js, JSModuleDef *m) {
    JS_SetModuleExportList(js, m, js_fmod_funcs, sizeof(js_fmod_funcs)/sizeof(JSCFunctionListEntry));
    FMOD_System_Init(sys, 2048, 0, NULL);
    
    return 0;
}

#ifdef JS_SHARED_LIBRARY
#define JS_INIT_MODULE js_init_module
#else
#define JS_INIT_MODULE js_init_module_fmod
#endif

JSModuleDef *JS_INIT_MODULE(JSContext *ctx, const char *module_name) {
    JSModuleDef *m = JS_NewCModule(ctx, module_name, js_fmod_init);
    if (!m) return NULL;
    JS_AddModuleExportList(ctx, m, js_fmod_funcs, sizeof(js_fmod_funcs)/sizeof(JSCFunctionListEntry));
    return m;
}

