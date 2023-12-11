#ifndef plainCursor_include_file
#define plainCursor_include_file

#ifdef __cplusplus
extern "C" {
#endif

#define plainCursor_width 16
#define plainCursor_height 16
#define plainCursor_size 130
#define plainCursor ((gfx_rletsprite_t*)plainCursor_data)
extern unsigned char plainCursor_data[130];

#ifdef __cplusplus
}
#endif

#endif
