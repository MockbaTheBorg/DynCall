// Two externs are necessary because functions returning integers will do it on RAX
// while functions returning floats will do it on XMM0 (can't cast)
// Not sure how to overcome this.
extern "C" uint64_t _DynCall_I(uint64_t);
extern "C" float _DynCall_F(uint64_t);