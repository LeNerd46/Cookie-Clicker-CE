#ifndef cursor_include_file
#define cursor_include_file

#ifdef __cplusplus
extern "C" {
#endif

#define cursor_width 7
#define cursor_height 11
#define cursor_size 84
#define cursor ((gfx_rletsprite_t*)cursor_data)
extern unsigned char cursor_data[84];

#ifdef __cplusplus
}
#endif

#endif
