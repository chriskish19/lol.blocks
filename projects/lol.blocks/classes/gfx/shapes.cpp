#include NAMES_INCLUDE
#include SHAPES_INCLUDE_PATH

lb::size_f lol_blocks::size::convert_wc()
{
    // multiply by scaling factor
    size_f wc = {};
    wc.szf_x = static_cast<float>(sz_x * (SF_X));
    wc.szf_y = static_cast<float>(sz_y * (SF_Y));
    wc.szf_z = static_cast<float>(sz_z * (SF_Z));

    return wc;
}
