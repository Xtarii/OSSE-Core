#ifndef OSSE_COLORS
#define OSSE_COLORS

/**
 * Converts x ( `number` ) to foreground color
 */
#define MAKE_FG_COLOR(x) ("\033[" #x "m")

/**
 * OSSE Color Namespace
 */
namespace OSSE::colors {
    /// Default Color ( Reset )
    inline const char* DEFAULT = MAKE_FG_COLOR(0);

    /// Red Color ( FG )
    inline const char* RED = MAKE_FG_COLOR(31);

    /// Yellow Color ( FG )
    inline const char* YELLOW = MAKE_FG_COLOR(33);



    /// Magenta Color ( FG )
    inline const char* MAGENTA = MAKE_FG_COLOR(35);

    /// Blue Color ( FG )
    inline const char* BLUE = MAKE_FG_COLOR(34);

    /// Cyan Color ( FG )
    inline const char* CYAN = MAKE_FG_COLOR(36);

    /// Green Color ( FG )
    inline const char* GREEN = MAKE_FG_COLOR(32);
}

#endif // OSSE_COLORS
