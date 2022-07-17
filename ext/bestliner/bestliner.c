#include <ruby.h>
#include "bestline.h"

static VALUE Bestliner;
static ID sym_id_call;

/* Callback Functions */

static void completionCallback(const char *buf, bestlineCompletions *lc) {
    VALUE proc, ary, str;
    long i, matches;
    proc = rb_iv_get(Bestliner, "@completion_callback");
    ary = rb_funcall(proc, sym_id_call, 1, rb_utf8_str_new_cstr(buf));
    Check_Type(ary, T_ARRAY);
    matches = RARRAY_LEN(ary);
    for (i = 0; i < matches; i++) {
        str = rb_obj_as_string(RARRAY_AREF(ary, i));
        bestlineAddCompletion(lc, StringValueCStr(str));
    }
}

static char *hintsCallback(const char *buf, const char **ansi1, const char **ansi2) {
    VALUE proc, str, a1, a2;
    proc = rb_iv_get(Bestliner, "@hints_callback");
    str = rb_funcall(proc, sym_id_call, 1, rb_utf8_str_new_cstr(buf));
    if (NIL_P(str)) {
        return NULL;
    } else {
        a1 = rb_iv_get(Bestliner, "@hints_before");
        if (!NIL_P(a1)) *ansi1 = StringValueCStr(a1);
        a2 = rb_iv_get(Bestliner, "@hints_after");
        if (!NIL_P(a2)) *ansi2 = StringValueCStr(a2);
        return StringValueCStr(str);
    }
}

/* Wrapper Functions */

static VALUE bestliner_bestline(VALUE self, VALUE prompt) {
    VALUE result;
    char *line;
    line = bestline(StringValueCStr(prompt));
    if (line == NULL) return Qnil;
    result = rb_utf8_str_new_cstr(line);
    free(line);
    return result;
}

static VALUE bestliner_bestlineWithHistory(VALUE self, VALUE prompt, VALUE filename) {
    VALUE result;
    char *line;
    line = bestlineWithHistory(StringValueCStr(prompt), StringValueCStr(filename));
    if (line == NULL) return Qnil;
    result = rb_utf8_str_new_cstr(line);
    free(line);
    return result;
}

static VALUE bestliner_bestlineRaw(VALUE self, VALUE prompt, VALUE in, VALUE out) {
    VALUE result;
    char *line;
    line = bestlineRaw(StringValueCStr(prompt), NUM2INT(in), NUM2INT(out));
    if (line == NULL) return Qnil;
    result = rb_utf8_str_new_cstr(line);
    free(line);
    return result;
}

static VALUE bestliner_bestlineHistoryAdd(VALUE self, VALUE line) {
    int rc;
    rc = bestlineHistoryAdd(StringValueCStr(line));
    return INT2NUM(rc);
}

static VALUE bestliner_bestlineHistorySave(VALUE self, VALUE filename) {
    int rc;
    rc = bestlineHistorySave(StringValueCStr(filename));
    return INT2NUM(rc);
}

static VALUE bestliner_bestlineHistoryLoad(VALUE self, VALUE filename) {
    int rc;
    rc = bestlineHistoryLoad(StringValueCStr(filename));
    return INT2NUM(rc);
}

static VALUE bestliner_bestlineHistoryFree(VALUE self) {
    bestlineHistoryFree();
    return Qnil;
}

static VALUE bestliner_bestlineClearScreen(VALUE self, VALUE out) {
    bestlineClearScreen(NUM2INT(out));
    return Qnil;
}

static VALUE bestliner_bestlineMaskModeEnable(VALUE self) {
    bestlineMaskModeEnable();
    return Qtrue;
}

static VALUE bestliner_bestlineMaskModeDisable(VALUE self) {
    bestlineMaskModeDisable();
    return Qfalse;
}

static VALUE bestliner_bestlineSetCompletionCallback(VALUE self, VALUE proc) {
    rb_iv_set(self, "@completion_callback", proc);
    bestlineSetCompletionCallback(completionCallback);
    return proc;
}

static VALUE bestliner_bestlineSetHintsCallback(VALUE self, VALUE proc) {
    rb_iv_set(self, "@hints_callback", proc);
    bestlineSetHintsCallback(hintsCallback);
    return proc;
}

void Init_bestliner(void) {
    /* Setup symbols */
    sym_id_call = rb_intern("call");
    /* Setup module */
    Bestliner = rb_define_module("Bestliner");
    rb_define_singleton_method(Bestliner, "__bestline", bestliner_bestline, 1);
    rb_define_singleton_method(Bestliner, "__bestline_with_history", bestliner_bestlineWithHistory, 2);
    rb_define_singleton_method(Bestliner, "__bestline_raw", bestliner_bestlineRaw, 3);
    rb_define_singleton_method(Bestliner, "__add_history", bestliner_bestlineHistoryAdd, 1);
    rb_define_singleton_method(Bestliner, "__save_history", bestliner_bestlineHistorySave, 1);
    rb_define_singleton_method(Bestliner, "__load_history", bestliner_bestlineHistoryLoad, 1);
    rb_define_singleton_method(Bestliner, "__free_history", bestliner_bestlineHistoryFree, 0);
    rb_define_singleton_method(Bestliner, "__clear_screen", bestliner_bestlineClearScreen, 1);
    rb_define_singleton_method(Bestliner, "__mask_mode_enable", bestliner_bestlineMaskModeEnable, 0);
    rb_define_singleton_method(Bestliner, "__mask_mode_disable", bestliner_bestlineMaskModeDisable, 0);
    rb_define_singleton_method(Bestliner, "__set_completion_cb", bestliner_bestlineSetCompletionCallback, 1);
    rb_define_singleton_method(Bestliner, "__set_hints_cb", bestliner_bestlineSetHintsCallback, 1);
}
